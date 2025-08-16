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
public:
    SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry);
    void loadFromFile(const json& j);
    void saveToFile(json& j) const;

private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
};
