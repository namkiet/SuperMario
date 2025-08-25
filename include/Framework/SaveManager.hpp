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

    std::string currentTimestamp();

public:
    SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry);

    std::string saveGame(const json& j, const std::string& saveDir);

    // wrapper cho ECS
    void loadFromFile(const json& j);
    void saveToFile(json& j) const;
};