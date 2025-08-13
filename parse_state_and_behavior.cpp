#include <clang-c/Index.h>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;

struct VisitorData {
    std::string className;
    std::string baseClassName;
};

struct ClientData {
    std::vector<VisitorData>* results;
    const std::string* currentFilePath;
    const std::vector<std::string>* suffixes;
};

// Visit base classes to check for suffix match
CXChildVisitResult baseVisitor(CXCursor c, CXCursor parent, CXClientData data) {
    VisitorData* vdata = static_cast<VisitorData*>(data);
    if (clang_getCursorKind(c) == CXCursor_CXXBaseSpecifier) {
        CXCursor baseClassCursor = clang_getCursorReferenced(c);
        CXString baseName = clang_getCursorSpelling(baseClassCursor);
        std::string baseNameStr = clang_getCString(baseName);
        clang_disposeString(baseName);

        vdata->baseClassName = baseNameStr;
    }
    return CXChildVisit_Continue;
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) {
    ClientData* data = static_cast<ClientData*>(client_data);

    if (clang_getCursorKind(cursor) == CXCursor_StructDecl || clang_getCursorKind(cursor) == CXCursor_ClassDecl) {
        // Only consider definitions
        if (!clang_isCursorDefinition(cursor)) return CXChildVisit_Continue;

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
            VisitorData vdata;

            // Check inheritance
            clang_visitChildren(cursor, baseVisitor, &vdata);

            // Check if base class matches any suffix
            if (!vdata.baseClassName.empty()) {
                for (const auto& suffix : *data->suffixes) {
                    if (vdata.baseClassName.size() >= suffix.size() &&
                        vdata.baseClassName.compare(vdata.baseClassName.size() - suffix.size(), suffix.size(), suffix) == 0) {

                        // Get class name
                        CXString className = clang_getCursorSpelling(cursor);
                        vdata.className = clang_getCString(className);
                        clang_disposeString(className);

                        data->results->push_back(vdata);
                        break;
                    }
                }
            }
        }

        clang_disposeString(fileName);
    }

    return CXChildVisit_Continue;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./parse <Suffix1> <Suffix2> ...\n";
        return 1;
    }

    std::vector<std::string> suffixes;
    for (int i = 1; i < argc; ++i) {
        suffixes.emplace_back(argv[i]);
    }

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

    outFile << "#include <StateManager.hpp>\n\n";

    std::vector<VisitorData> allResults;

    for (const auto& file : files) {
        std::vector<VisitorData> results;

        CXTranslationUnit unit = clang_parseTranslationUnit(
            index,
            file.c_str(),
            args, sizeof(args)/sizeof(args[0]),
            nullptr, 0,
            CXTranslationUnit_None
        );

        if (!unit) continue;

        CXCursor rootCursor = clang_getTranslationUnitCursor(unit);
        ClientData cd{ &results, &file, &suffixes };
        clang_visitChildren(rootCursor, visitor, &cd);

        for (const auto& res : results) {
            allResults.push_back({res.className, res.baseClassName});

            std::string includePath = file;
            const std::string prefix = "include/";
            if (includePath.rfind(prefix, 0) == 0) {
                includePath = includePath.substr(prefix.size());
            }

            outFile << "#include <" << includePath << ">\n";
        }
        clang_disposeTranslationUnit(unit);
    }

    outFile << "\n";
    for (const auto& res : allResults) {
        outFile << "DEFINE_STATE(" << res.baseClassName << ", " << res.className << ")\n";
    }

    clang_disposeIndex(index);
    outFile.close();

    return 0;
}
