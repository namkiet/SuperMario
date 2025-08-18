#pragma once
#include <imgui.h>
#include <nlohmann/json.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>
#include <Engine/Animation/Animation.hpp>
#include <ECS/Entity.hpp>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

class EntityEditor {
public:
    EntityEditor(EntityManager& em, ComponentRegistry& cr, json& sceneData);

    void update(float dt);
    void display(sf::RenderWindow& window) const;

    std::string getSelectedEntityId() const { return selectedEntityId; }

    void handleClick();

private:
    void drawEntityExplorer();
    void drawPrefabPanel();
    void createNewEntity();

    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    json& sceneData;

    std::string selectedEntityId;
    Entity* selectedEntity = nullptr;
    Entity* draggedEntity = nullptr;


    bool forceCollapseHeaders = false;

    // std::unordered_map<std::string, std::function<std::shared_ptr<Entity>()>> prefabFactories;

    struct PrefabInfo {
        std::string name;
        Animation animation;
        std::function<Entity*(float, float)> factory; // spawn entity at x,y
    };

    std::vector<PrefabInfo> prefabList;
    PrefabInfo* selectedPrefab = nullptr; // currently selected prefab to place

    mutable sf::Vector2f mousePos;
    mutable sf::Vector2f lastMousePos;
    bool isDraggingScreen = false;

};
