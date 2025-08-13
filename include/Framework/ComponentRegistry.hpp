#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <ECS/Entity.hpp>
#include <Core/Utility.hpp>

using json = nlohmann::json;


class ComponentRegistry {
public:
    template<typename T>
    static void registerComponent() {
        auto name = get_type_name<T>();
        saveByType[name] = [](EntityManager& em, json& j) {
            for (auto entity : em.findAll()) {
                if (entity->hasComponent<T>()) {
                    j[std::to_string(entity->getID())][get_type_name<T>()] = entity->getComponent<T>();
                }
            }
        };
        loadByType[name] = [](const json& j, Entity* e) {
            e->addComponent<T>(j);
        };
    }

    void saveComponents(EntityManager& em, json& j) {
        for (auto& [_, saveFunc] : saveByType) saveFunc(em, j);
    }

    void loadComponents(const json& j, EntityManager& em) {
        for (auto& [id, data] : j.items()) {
            for (auto& [name, compJSON] : data.items()) {
                if (loadByType.find(name) != loadByType.end()) {
                    loadByType[name](compJSON, em.getEntityByID(std::stoi(id)));
                }
            }
        }
    }

private:
    static inline std::unordered_map<std::string, std::function<void(EntityManager&, json&)>> saveByType;
    static inline std::unordered_map<std::string, std::function<void(const json&, Entity*)>> loadByType;
};
