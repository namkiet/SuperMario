#include <Game.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp> // cần thư viện JSON

namespace fs = std::filesystem;
using json = nlohmann::json;

void initDirectoryForSave(const std::string& saveDir)
{
    // Tạo thư mục saves/
    fs::create_directories(saveDir + "/screenshots");

    // Kiểm tra và tạo file index.json nếu chưa có
    fs::path indexPath = saveDir + "/index.json";
    if (!fs::exists(indexPath)) {
        json j;
        j["count"] = 0;
        j["saves"] = json::array();

        std::ofstream ofs(indexPath);
        if (!ofs) {
            std::cerr << "Failed to create " + saveDir + "/index.json\n";
            exit(0);
        }
        ofs << j.dump(4); // dump với indent = 4 cho dễ đọc
        ofs.close();

        std::cout << "Created " + saveDir + "/index.json with default content\n";
    }
}

int main()
{
    try
    {
        initDirectoryForSave("saves");
        initDirectoryForSave("customs");
        Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }

    return 0;
}
