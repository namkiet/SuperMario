#include <Framework/SaveManager.hpp>
#include <ctime>

SaveManager::SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry, const std::string& dir)
    : entityManager(entityManager)
    , componentRegistry(componentRegistry)
    , saveDir(dir)
    , indexPath(dir + "/index.json")
{
    loadIndex();
}

std::string SaveManager::currentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    return std::string(buf);
}

json SaveManager::loadIndex() {
    std::ifstream f(indexPath);
    if (!f.is_open()) {
        // nếu chưa có thì trả về cấu trúc mặc định
        return {
            {"count", 0},
            {"saves", json::array()}
        };
    }
    json j;
    f >> j;
    return j;
}


void SaveManager::saveIndex(const json& j) {
    std::ofstream f(indexPath);
    f << j.dump(4);
}

std::string SaveManager::saveGame(const json& j) {
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

    // load index cũ
    json index = loadIndex();

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

    saveIndex(index);

    return timestamp;
}


void SaveManager::loadGame(int slot) {
    if (slot < 1 || slot > 9) {
        throw std::runtime_error("Slot must be 1-9");
    }

    std::string slotFile = saveDir + "/save_slot_" + std::to_string(slot) + ".json";
    std::ifstream f(slotFile);
    if (!f.is_open()) {
        throw std::runtime_error("Save file not found for slot " + std::to_string(slot));
    }

    json gameData;
    f >> gameData;
    loadFromFile(gameData);
}

json SaveManager::getIndex() {
    return loadIndex();
}

// gọi sang ComponentRegistry
void SaveManager::loadFromFile(const json& j) {
    componentRegistry.loadComponents(j, entityManager);
}

void SaveManager::saveToFile(json& j) const {
    j.clear();
    componentRegistry.saveComponents(entityManager, j);
}