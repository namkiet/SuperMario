#include <Framework/ComponentRegistry.hpp>

void ComponentRegistry::saveComponents(EntityManager& em, json& j) const {
    for (auto entity : em.findAll())
    {
        saveComponents(entity, j[std::to_string(entity->getID())]);
    }
}

void ComponentRegistry::saveComponents(Entity* entity, json& j) const
{
    j.clear();

    if (!entity) return;
    j["name"] = entity->getName();
    for (auto& [_, saveFunc] : saveByType)
    {
        saveFunc(entity, j);
    }
}

void ComponentRegistry::loadComponents(const json& j, EntityManager& em) {
    em.removeAllEntities();
    for (auto& [id, data] : j.items()) 
    {
        em.createEntity(stoi(id), data["name"]);
    }

    for (auto entity : em.findAll())
    {
        loadComponents(j[std::to_string(entity->getID())], entity);
    }
}

void ComponentRegistry::loadComponents(const json& j, Entity* entity) {

    if (!entity) return;

    int id = entity->getID();
    for (auto& [compName, compJSON] : j.items()) 
    {
        if (compName == "name") continue;

        if (loadByType.find(compName) != loadByType.end()) 
        {
            try
            {
                loadByType[compName](compJSON, entity);
            }
            catch(const std::exception& e)
            {
                std::cerr << id << " -- " << compName << " -- " << e.what() << '\n';
            }
        }
    }
}
