#pragma once
#include <Framework/EntityManager.hpp>
#include <unordered_map>
#include <functional>
#include <string>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <ECS/Entity.hpp>
#include <iostream>
#include <sstream>

using json = nlohmann::json;


class ComponentRegistry {
public:
    template<typename T>
    static void registerComponent(const std::string& compName) {
        saveByType[compName] = [compName](Entity* entity, json& j) {
            if (entity->hasComponent<T>()) {
                j[std::to_string(entity->getID())][compName] = entity->getComponent<T>();
            }
        };
        loadByType[compName] = [](const json& j, Entity* e) {
            T comp = j;
            e->addComponent<T>(comp);
        };
    }

    void saveComponents(EntityManager& em, json& j) const;
    void saveComponents(Entity* entity, json& j) const;
    void loadComponents(const json& j, EntityManager& em);
    void loadComponents(const json& j, Entity* entity);

private:
    static inline std::unordered_map<std::string, std::function<void(Entity*, json&)>> saveByType;
    static inline std::unordered_map<std::string, std::function<void(const json&, Entity*)>> loadByType;
};
