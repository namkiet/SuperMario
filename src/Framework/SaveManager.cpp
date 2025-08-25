#include <Framework/SaveManager.hpp>
#include <ctime>

SaveManager::SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry)
    : entityManager(entityManager)
    , componentRegistry(componentRegistry) {}

std::string SaveManager::currentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    return std::string(buf);
}


std::string SaveManager::saveGame(const json& j, const std::string& saveDir) {
    // Tạo tên file theo timestamp, thay space bằng _
    std::string timestamp = currentTimestamp();
    for (auto& c : timestamp) {
        if (c == ' ') c = '_';
    }
    std::string filename = timestamp + ".json";
    std::string slotFile = saveDir + "/" + filename;

    // ghi dữ liệu game
    std::ofstream f(slotFile);
    f << j.dump(4);

    std::string indexPath = saveDir + "/index.json";

    // load index cũ
    std::ifstream fin(indexPath);
    json index; fin >> index;

    // nếu chưa có cấu trúc, tạo mới
    if (!index.is_object()) {
        index = json::object();
        index["count"] = 0;
        index["saves"] = json::array();
    }

    // tạo metadata
    json meta;
    meta["filename"]  = filename;
    meta["timestamp"] = timestamp;
    meta["level"]     = j.value("level", 0);
    meta["lives"]     = j.value("lives", 5);

    // push vào mảng saves
    index["saves"].push_back(meta);

    // update count = số phần tử hiện có
    index["count"] = index["saves"].size();

    // nếu muốn giữ tối đa 9 bản
    if (index["saves"].size() > 9) {
        index["saves"].erase(index["saves"].begin());
        index["count"] = index["saves"].size();
    }

    std::ofstream f2(indexPath);
    f2 << index.dump(4);

    return timestamp;
}

// gọi sang ComponentRegistry
void SaveManager::loadFromFile(const json& j) {
    componentRegistry.loadComponents(j, entityManager);
}

void SaveManager::saveToFile(json& j) const {
    j.clear();
    componentRegistry.saveComponents(entityManager, j);
}