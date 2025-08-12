#include <clang-c/Index.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

struct VisitorData {
    bool inheritsFromComponent = false;
    std::string className;
    std::vector<std::string> fields;
};

struct ClientData {
    std::vector<VisitorData>* results;
    const std::string* currentFilePath;
};

// Visit base classes to check for Component
CXChildVisitResult baseVisitor(CXCursor c, CXCursor parent, CXClientData data) {
    VisitorData* vdata = static_cast<VisitorData*>(data);
    if (clang_getCursorKind(c) == CXCursor_CXXBaseSpecifier) {
        CXCursor baseClassCursor = clang_getCursorReferenced(c);
        CXString baseName = clang_getCursorSpelling(baseClassCursor);
        const char* baseNameCStr = clang_getCString(baseName);
        if (baseNameCStr && std::string(baseNameCStr) == "Component") {
            vdata->inheritsFromComponent = true;
        }
        clang_disposeString(baseName);
    }
    return CXChildVisit_Continue;
}

// Visit fields
CXChildVisitResult fieldVisitor(CXCursor c, CXCursor parent, CXClientData data) {
    VisitorData* vdata = static_cast<VisitorData*>(data);
    if (clang_getCursorKind(c) == CXCursor_FieldDecl) {
        CXString fieldName = clang_getCursorSpelling(c);
        vdata->fields.push_back(clang_getCString(fieldName));
        clang_disposeString(fieldName);
    }
    return CXChildVisit_Continue;
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
    ClientData* data = static_cast<ClientData*>(client_data);

    if (clang_getCursorKind(cursor) == CXCursor_StructDecl || clang_getCursorKind(cursor) == CXCursor_ClassDecl) {
        // Check if declared in the current file
        CXSourceLocation loc = clang_getCursorLocation(cursor);
        CXFile cursorFile;
        unsigned line, column, offset;
        clang_getExpansionLocation(loc, &cursorFile, &line, &column, &offset);

        CXString fileName = clang_getFileName(cursorFile);
        const char* cursorFileName = clang_getCString(fileName);

        bool isDeclaredInCurrentFile =
            (cursorFileName && data->currentFilePath &&
             *data->currentFilePath == std::string(cursorFileName));

        if (isDeclaredInCurrentFile) {
            VisitorData vdata = {};

            // Check inheritance
            clang_visitChildren(cursor, baseVisitor, &vdata);

            if (vdata.inheritsFromComponent) {
                // Get class name
                CXString className = clang_getCursorSpelling(cursor);
                vdata.className = clang_getCString(className);
                clang_disposeString(className);

                // Get fields
                clang_visitChildren(cursor, fieldVisitor, &vdata);

                data->results->push_back(vdata);
            }
        }

        clang_disposeString(fileName);
    }

    return CXChildVisit_Continue;
}

int main() {
    CXIndex index = clang_createIndex(0, 0);

    std::string folder = "include/";
    std::vector<std::string> files;

    // Recursively gather files
    for (const auto& entry : fs::recursive_directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            auto path = entry.path();
            if (path.extension() == ".hpp" || path.extension() == ".cpp") {
                files.push_back(path.string());
            }
        }
    }

    const char* args[] = {
        "-std=c++17",
        "-Iinclude"
    };

    std::ofstream outFile("out.h");
    if (!outFile.is_open()) {
        std::cerr << "Failed to open out.h for writing." << std::endl;
        return -1;
    }

    outFile << "#include <jsonSFML.hpp>\n\n";

    for (const auto& file : files) {
        std::vector<VisitorData> results;

        CXTranslationUnit unit = clang_parseTranslationUnit(
            index,
            file.c_str(),
            args, sizeof(args)/sizeof(args[0]),
            nullptr, 0,
            CXTranslationUnit_None
        );

        if (!unit) {
            continue;
        }

        CXCursor rootCursor = clang_getTranslationUnitCursor(unit);
        ClientData cd{ &results, &file };
        clang_visitChildren(rootCursor, visitor, &cd);

        if (!results.empty()) {
            // print include first
            outFile << "#include <" << file << ">\n\n";
            for (const auto& res : results) {
                outFile << "REGISTER_COMPONENT(" << res.className << ")\n";
                if (!res.fields.empty()) {
                    outFile << "NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE("
                            << res.className;
                    for (const auto& field : res.fields) {
                        outFile << ", " << field;
                    }
                    outFile << ")\n";
                }
                else
                {
                    outFile << "DEFINE_TAG(" << res.className << ")\n";
                }
                outFile << "\n";
            }
        }

        clang_disposeTranslationUnit(unit);
    }

    clang_disposeIndex(index);
    outFile.close();

    return 0;
}
