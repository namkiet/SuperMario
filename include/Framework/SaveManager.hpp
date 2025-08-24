#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>
#include <sstream>

using json = nlohmann::json;

class SaveManager 
{
private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;

    std::string saveDir;
    std::string indexPath;

    std::string currentTimestamp();
    json loadIndex();
    void saveIndex(const json& j);

public:
    SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry, const std::string& dir = "saves");

    std::string saveGame(const json& j);
    void loadGame(int slot);
    json getIndex();

    // wrapper cho ECS
    void loadFromFile(const json& j);
    void saveToFile(json& j) const;
};