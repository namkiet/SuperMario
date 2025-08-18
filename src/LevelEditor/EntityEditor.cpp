#include <LevelEditor/EntityEditor.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Bowser/Bowser.hpp>
#include <iostream>
#include <sstream>
#include <Engine/Core/Transform.hpp>
#include <Engine/Camera/Camera.hpp>

struct AnimationButtonInfo {
    ImTextureID textureID;
    ImVec2 uv0;
    ImVec2 uv1;
    ImVec2 size;
};

inline AnimationButtonInfo getAnimationButtonInfo(const Animation& anim, float buttonSize = 48.f) {
    AnimationButtonInfo info{};
    if (!anim.sprite.getTexture()) return info;

    const sf::Texture* tex = anim.sprite.getTexture();
    sf::IntRect rect = anim.sprite.getTextureRect();

    float texWidth = float(tex->getSize().x);
    float texHeight = float(tex->getSize().y);

    info.textureID = (ImTextureID)tex->getNativeHandle();
    info.uv0 = ImVec2(rect.left / texWidth, rect.top / texHeight);
    info.uv1 = ImVec2((rect.left + rect.width) / texWidth, (rect.top + rect.height) / texHeight);
    info.size = ImVec2(buttonSize, buttonSize);

    return info;
}


EntityEditor::EntityEditor(EntityManager& em, ComponentRegistry& cr, json& sceneData)
    : entityManager(em), componentRegistry(cr), sceneData(sceneData) 
{
    prefabList.push_back({
        "Goomba",
        Animation(TextureManager::load("assets/Enemy/Goomba/goomba_walk.png"), 16, 16, 2, 0.25f),
        [this](float x, float y) { return entityManager.createEntity<Goomba>(x / 3, y / 3, 3.f); }
    });

    prefabList.push_back({
        "Koopa",
        Animation(TextureManager::load("assets/Enemy/Koopa/koopa_walk.png"), 16, 24, 2, 0.25f),
        [this](float x, float y) { return entityManager.createEntity<Koopa>(x / 3, y / 3, 3.f); }
    });

    prefabList.push_back({
        "Bowser",
        Animation(TextureManager::load("assets/Enemy/Bowser/bowser_walk.png"), 32, 35, 4, 0.25f),
        [this](float x, float y) { return entityManager.createEntity<Bowser>(x / 3, y / 3, 3.f); }
    });
}


void EntityEditor::update(float dt)
{
    handleClick();

    for (auto& prefab: prefabList)
    {
        updateAnimation(prefab.animation, dt);
    }

    ImGui::BeginChild("EntitiesPanel", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    drawPrefabPanel();
    drawEntityExplorer();
    ImGui::EndChild();
}

void EntityEditor::display(sf::RenderWindow& window) const
{
    auto cam = entityManager.findFirst<Camera>();
    if (!cam) return;

    auto& camTarget = cam->getComponent<Camera>().target;

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    mousePos = camTarget + sf::Vector2f(pixelPos.x, pixelPos.y) - 0.5f * sf::Vector2f(window.getSize().x, window.getSize().y);

    // Fix: Dragging screen moves camera smoothly based on mouse movement
    if (isDraggingScreen)
    {
        // camTarget.x -= pixelPos.x - lastMousePos.x; // Move camera opposite to mouse drag
        // lastMousePos = mousePos;
    }

    std::cout << mousePos.x << " " << mousePos.y << "\n";
}

void EntityEditor::drawPrefabPanel() 
{
    ImGui::Text("Prefabs");
    ImGui::Separator();

    int columns = 4;
    ImGui::Columns(columns, nullptr, false);

    for (auto& prefab : prefabList) {
        AnimationButtonInfo btn = getAnimationButtonInfo(prefab.animation, 24.f);

        if (ImGui::ImageButton(btn.textureID, btn.size, btn.uv0, btn.uv1)) {
            selectedPrefab = &prefab;
        }

        ImGui::TextWrapped("%s", prefab.name.c_str());
        ImGui::NextColumn();
    }

    ImGui::Columns(1);

    // Create new entity as a plain button
    if (ImGui::Button("Create New Entity")) {
        createNewEntity();
    }

    ImGui::Separator();
}


void EntityEditor::createNewEntity() {
    // auto entity = std::make_shared<Entity>();
    // std::string key = "Entity " + std::to_string(entity->getID());
    // sceneData[key] = entity->serializeToJson();
    // entityManager.addEntity(entity.get());
    // selectedEntityId = key;
    // forceCollapseHeaders = true;
}

void EntityEditor::drawEntityExplorer() {
    for (auto& [entityName, entity] : sceneData.items()) {
        bool selected = (selectedEntityId == entityName);
        if (ImGui::Selectable(entityName.c_str(), selected)) {
            if (selectedEntityId != entityName) forceCollapseHeaders = true;
            selectedEntityId = entityName;

            std::istringstream iss(entityName);
            std::string _;
            int id;
            iss >> _ >> id;
            
            selectedEntity = entityManager.getEntityByID(id);
        }
    }
}

void EntityEditor::handleClick()
{
    isDraggingScreen = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (selectedPrefab)
        {
            selectedPrefab->factory(mousePos.x, mousePos.y);
            selectedPrefab = nullptr;
        }
        else
        {
            if (!draggedEntity)
            {
                for (Entity* e : entityManager.findAll<Transform, Animation>())
                {
                    auto& t = e->getComponent<Transform>();
                    sf::FloatRect bounds(t.position.x, t.position.y, t.size.x, t.size.y); 
                    if (bounds.contains(mousePos))
                    {
                        draggedEntity = e;
                        break;
                    }
                }

                // if (!draggedEntity)
                // {
                //     lastMousePos = mousePos;
                //     isDraggingScreen = true;
                // }
            }
            else
            {
                draggedEntity->getComponent<Transform>().position = mousePos - 0.5f * draggedEntity->getComponent<Transform>().size;
            }
        }
    }
    else // mouse released
    {
        draggedEntity = nullptr;
    }
}