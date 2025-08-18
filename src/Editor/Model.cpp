#include <Editor/Model.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Camera/Camera.hpp>
#include <string>

Model::Model(EntityManager& entityManager, ComponentRegistry& componentRegistry)
    : entityManager(entityManager), componentRegistry(componentRegistry) 
{
    sceneData.clear();
    componentRegistry.saveComponents(entityManager, sceneData);   
}

void Model::addEntity(std::unique_ptr<Entity> entity)
{
    entityManager.addEntity(std::move(entity));
}

void Model::removeEntity(float x, float y)
{
    for (auto entity : entityManager.findAll<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        sf::FloatRect bounds(tf.position, tf.size);
        if (bounds.contains(sf::Vector2f(x, y)))
        {
            entityManager.destroyEntity(entity);
            break;
        }
    }
}

Entity* Model::getEntityAt(float x, float y)
{
    for (auto entity : entityManager.findAll<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        sf::FloatRect bounds(tf.position, tf.size);
        if (bounds.contains(sf::Vector2f(x, y))) return entity;
    }
    return nullptr;
}

sf::Vector2f& Model::getCameraCenter() const
{
    return entityManager.findFirst<Camera>()->getComponent<Camera>().target;
}

json Model::getEntityInfo(Entity* entity) const
{
    json j;
    if (!entity) return j;

    int id = entity->getID();
    componentRegistry.saveComponents(entity, j);
    return j[std::to_string(id)];
}

void Model::updateEntityInfo(Entity* entity, const json& newData)
{
    componentRegistry.loadComponents(newData, entity);
}