#include <Framework/SaveManager.hpp>

SaveManager::SaveManager(EntityManager& entityManager, ComponentRegistry& componentRegistry)
    : entityManager(entityManager)
    , componentRegistry(componentRegistry) {}

void SaveManager::loadFromFile(const json& j) 
{
    componentRegistry.loadComponents(j, entityManager);
}

void SaveManager::saveToFile(json& j) const 
{
    j.clear();
    componentRegistry.saveComponents(entityManager, j);
}