#pragma once
#include <Framework/EntityManager.hpp>
#include <unordered_map>
#include <functional>
#include <string>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <ECS/Entity.hpp>
#include <iostream>

using json = nlohmann::json;


class ComponentRegistry {
public:
    template<typename T>
    static void registerComponent(const std::string& name) {
        saveByType[name] = [name](EntityManager& em, json& j) {
            for (auto entity : em.findAll()) {
                if (entity->hasComponent<T>()) {
                    j[std::to_string(entity->getID())][name] = entity->getComponent<T>();
                }
            }
        };
        loadByType[name] = [](const json& j, Entity* e) {
            T comp = j;
            e->addComponent<T>(comp);
        };
    }

    void saveComponents(EntityManager& em, json& j) const {
        for (auto& [_, saveFunc] : saveByType) saveFunc(em, j);
    }

    void loadComponents(const json& j, EntityManager& em) {
        for (auto& [id, data] : j.items()) {
            for (auto& [name, compJSON] : data.items()) {
                if (loadByType.find(name) != loadByType.end()) 
                {
                    try
                    {
                        loadByType[name](compJSON, em.getEntityByID(std::stoi(id)));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << id << " " << name << " " << e.what() << '\n';
                    }
                }
            }
        }
    }

private:
    static inline std::unordered_map<std::string, std::function<void(EntityManager&, json&)>> saveByType;
    static inline std::unordered_map<std::string, std::function<void(const json&, Entity*)>> loadByType;
};
