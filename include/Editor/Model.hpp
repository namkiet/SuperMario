#pragma once
#include <nlohmann/json.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>
#include <ECS/Entity.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

using json = nlohmann::json;

class Model
{
public:
    Model(EntityManager& entityManager, ComponentRegistry& componentRegistry);
    void addEntity(std::unique_ptr<Entity> entity);
    void removeEntity(float x, float y);
    Entity* getEntityAt(float x, float y);
    sf::Vector2f& getCameraCenter() const;
    json getEntityInfo(Entity* entity) const;
    void updateEntityInfo(Entity* entity, const json& newData);

private:
    EntityManager& entityManager;
    ComponentRegistry& componentRegistry;
    json sceneData;
};