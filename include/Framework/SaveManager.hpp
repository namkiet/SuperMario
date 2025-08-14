#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
// #include <imgui.h>
// #include <imgui-SFML.h>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>

using json = nlohmann::json;

class SaveManager {
public:
    SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry)
        : entityManager(entityManager), componentRegistry(componentRegistry) {}

    void loadFromFile(const json& j) {
        // std::ifstream file(filename);
        // if (!file.is_open()) return;
        // file >> sceneData;
        // entityManager.removeAllEntities();
        // for (auto& [id, _] : sceneData.items()) {
        //     entityManager.createEntity(std::stoi(id));
        // }
        // componentRegistry.loadComponents(sceneData, entityManager);


        entityManager.removeAllEntities();
        for (auto& [id, _] : j.items()) {
            entityManager.createEntity(std::stoi(id));
        }
        componentRegistry.loadComponents(j, entityManager);
    }

    void saveToFile(json& j) const {
        // sceneData.clear();
        // componentRegistry.saveComponents(entityManager, sceneData);
        // std::ofstream outFile(filename);
        // if (outFile.is_open()) outFile << sceneData.dump(4);
        j.clear();
        componentRegistry.saveComponents(entityManager, j);
    }

private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    // json sceneData;
};
