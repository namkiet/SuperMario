#include <Game.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp> // cần thư viện JSON

namespace fs = std::filesystem;
using json = nlohmann::json;

int main()
{
    try {
        // Tạo thư mục saves/
        fs::create_directories("saves/screenshots");

        // Kiểm tra và tạo file index.json nếu chưa có
        fs::path indexPath = "saves/index.json";
        if (!fs::exists(indexPath)) {
            json j;
            j["count"] = 0;
            j["saves"] = json::array();

            std::ofstream ofs(indexPath);
            if (!ofs) {
                std::cerr << "Failed to create saves/index.json\n";
                return 1;
            }
            ofs << j.dump(4); // dump với indent = 4 cho dễ đọc
            ofs.close();

            std::cout << "Created saves/index.json with default content\n";
        }
    }
    catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to initialize saves folder: " << e.what() << "\n";
        return 1;
    }

    std::ofstream fout("output.txt");
    if (fout.fail())
    {
        std::cerr << "Failed to open output.txt for writing." << std::endl;
        return 1;
    }

    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }

    fout.close();
    return 0;
}
