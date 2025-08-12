#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>

using json = nlohmann::json;

class SaveManager {
public:
    SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry)
        : entityManager(entityManager), componentRegistry(componentRegistry) {}

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        file >> sceneData;
        entityManager.removeAllEntities();
        for (auto& [id, _] : sceneData.items()) {
            entityManager.createEntity(std::stoi(id));
        }
        componentRegistry.loadComponents(sceneData, entityManager);
    }

    void saveToFile(const std::string& filename) {
        sceneData.clear();
        componentRegistry.saveComponents(entityManager, sceneData);
        std::ofstream outFile(filename);
        if (outFile.is_open()) outFile << sceneData.dump(4);
    }

private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    json sceneData;
};
