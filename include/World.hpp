#pragma once
#include <ECS/Entity.hpp>
#include <ECS/System.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <algorithm>
#include <functional>
#include <cxxabi.h>

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template<typename T>
std::string get_type_name() {
    int status;
    char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    std::string result = (status == 0) ? demangled : typeid(T).name();
    free(demangled);
    return result;
}

class World
{
public:
    static World& getInstance()
    {
        static World instance;
        return instance;
    }

private:
    World() = default;
    ~World() = default;

    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

private:
    // 🧠 Component serialization maps
    std::unordered_map<std::string, std::function<void(World& world, json& j)>> saveByType;
    std::unordered_map<std::string, std::function<void(const json& j, Entity* entity)>> loadByType;

public:
    // ✅ Register a component type
    template <typename T>
    void registerComponent()
    {
        auto name = get_type_name<T>();

        saveByType[name] = [](World& world, json& j)
        {
            world.saveToJSON<T>(j);
        };

        loadByType[name] = [](const json& j, Entity* entity)
        {
            T comp = j;
            entity->addComponent<T>(comp);
        };
    }

    template <typename T>
    void saveToJSON(json& j)
    {
        int id = 0;
        for (const auto& entity : entities)
        {
            if (entity->hasComponent<T>())
            {
                j[std::to_string(id)][get_type_name<T>()] = entity->getComponent<T>();
            }
            ++id;
        }
    }

    // ✅ Save all entities and components to JSON
    void saveToJSON(json& j)
    {
        for (const auto& [_, saver] : saveByType)
        {
            saver(*this, j);
        }
    }

    void loadFromJSON(const json& j)
    {
        for (const auto& [id, data] : j.items())
        {
            Entity* entity = createEntity();

            for (const auto& [name, compJSON] : data.items())
            {
                if (loadByType.find(name) == loadByType.end()) continue;
                loadByType[name](compJSON, entity);
            }

        }
    }


public:
    Entity *createEntity()
    {
        entities.push_back(std::make_unique<Entity>());
        return entities.back().get();
    }

    template <typename T, typename... Args>
    Entity *createEntity(Args &&...args)
    {
        entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return entities.back().get();
    }

    Entity *createEntityAtFront()
    {
        entities.insert(entities.begin(), std::make_unique<Entity>());
        return entities.front().get();
    }

    template <typename T, typename... Args>
    Entity *createEntityAtFront(Args &&...args)
    {
        entities.insert(entities.begin(), std::make_unique<T>(std::forward<Args>(args)...));
        return entities.front().get();
    }

    void deleteEntity(Entity *entity)
    {
        auto it = std::remove_if(entities.begin(), entities.end(), [entity](const std::unique_ptr<Entity> &e)
                                 { return e.get() == entity; });
        if (it != entities.end())
        {
            entities.erase(it, entities.end());
        }
    }

    void destroyEntity(Entity *entity)
    {
        // destroyPending.push_back(entity);
        deleteEntity(entity);
    }

    std::vector<Entity *> findAll() const
    {
        std::vector<Entity *> result;
        for (auto &e : entities)
        {
            result.push_back(e.get());
        }
        return result;
    }

    template <typename... T>
    std::vector<Entity *> findAll() const
    {
        std::vector<Entity *> result;
        for (auto &e : entities)
        {
            if ((e->hasComponent<T>() && ...))
            {
                result.push_back(e.get());
            }
        }
        return result;
    }

    template <typename... T>
    Entity *findFirst() const
    {
        for (auto &e : entities)
        {
            if ((e->hasComponent<T>() && ...))
            {
                return e.get();
            }
        }
        return nullptr;
    }

    template <typename T>
    void addSystem()
    {
        // static_assert(std::is_base_of<System, T>::value, "T must inherit from System");

        auto system = std::make_shared<T>();
        systems[typeid(T)] = system;
        orderedSystems.push_back(system);
    }

    template <typename T>
    std::shared_ptr<T> getSystem() const
    {
        auto it = systems.find(typeid(T));
        if (it == systems.end())
        {
            throw std::runtime_error("System not found");
        }

        return std::static_pointer_cast<T>(it->second);
    }

    void update(float deltaTime)
    {
        for (auto &system : orderedSystems)
        {
            system->preUpdate(*this, deltaTime);
        }
        // int i = 0;
        for (auto &system : orderedSystems)
        {
            // i += 1;
            system->update(*this, deltaTime);
            // auto player = findFirst<PlayerTag>();
            // if (!player) continue;
            // auto rb = player->getComponent<RigidBody>();
            // std::cout << i <<" rb.velocity.y = " << rb.velocity.y << std::endl;
        }

        for (auto &system : orderedSystems)
        {
            system->postUpdate(*this, deltaTime);
        }

        for (Entity *entity : destroyPending)
        {
            deleteEntity(entity);
        }

        destroyPending.clear();
    }

    void removeAllEntities()
    {
        for (auto &entity : entities)
            deleteEntity(entity.get());
        entities.clear();
        for (Entity *entity : destroyPending)
        {
            deleteEntity(entity);
        }
        destroyPending.clear();
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::vector<std::shared_ptr<System>> orderedSystems;
    std::vector<Entity *> destroyPending;
};

// #pragma once
// #include <ECS/Entity.hpp>
// #include <ECS/System.hpp>
// #include <Modules/BaseModule.hpp>
// #include <memory>
// #include <stdexcept>
// #include <unordered_map>
// #include <unordered_set>
// #include <typeindex>
// #include <vector>
// #include <functional>
// #include <cxxabi.h>


// template<typename T>
// std::string get_type_name() {
//     int status;
//     char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
//     std::string result = (status == 0) ? demangled : typeid(T).name();
//     free(demangled);
//     return result;
// }

// class World 
// {
// public:
//     template <typename T>
//     void addModule()
//     {
//         auto newModule = std::make_unique<T>();
//         newModule->registerComponent(*this);
//         newModule->registerSystem(*this);
//     }

// private:
//     // 🧠 Component serialization maps
//     std::unordered_map<std::string, std::function<bool(Entity*)>> hasMap;
//     std::unordered_map<std::string, std::function<void(Entity*)>> addMap;
//     std::unordered_map<std::string, std::function<Component&(Entity*)>> getMap;

// public:
//     // ✅ Register a component type
//     template <typename T>
//     void registerComponent()
//     {
//         auto name = get_type_name<T>();

//         hasMap[name] = [](Entity* e) {
//             return e->hasComponent<T>();
//         };

//         addMap[name] = [](Entity* e) {
//             e->addComponent<T>();
//         };

//         getMap[name] = [](Entity* e) -> Component& {
//             return e->getComponent<T>();
//         };
//     }

//     // ✅ Save all entities and components to JSON
//     void saveToJSON(json& j)
//     {
//         int id = 0;
//         for (const auto& entity : entities)
//         {
//             for (const auto& [name, hasFunc] : hasMap)
//             {
//                 if (hasFunc(entity.get()))
//                 {
//                     Component& comp = getMap[name](entity.get());

//                     json compJson;
//                     comp.serialize(compJson);  // Component must implement serialize()
//                     j[std::to_string(id)][name] = compJson;
//                 }
//             }
//             ++id;
//         }
//     }

//     void loadFromJSON(const json& j)
//     {
//         for (auto& [id, componentsJson] : j.items())
//         {
//             Entity* entity = createEntity();

//             for (const auto& [name, compJson] : componentsJson.items())
//             {
//                 if (addMap.find(name) != addMap.end())
//                 {
//                     addMap[name](entity);
//                     Component& c = getMap[name](entity);
//                     c.deserialize(compJson); // Component must implement deserialize()
//                 }
//             }
//         }
//     }

//     Entity* createEntity() 
//     {
//         entities.push_back(std::make_unique<Entity>());
//         return entities.back().get();
//     }

//     template<typename T, typename... Args>
//     Entity* createEntity(Args&&... args)
//     {
//         entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
//         return entities.back().get();
//     }
    
//     void deleteEntity(Entity* entity)
//     {
//         auto it = std::remove_if(entities.begin(), entities.end(), [entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; });
//         if (it != entities.end()) 
//         {
//             entities.erase(it, entities.end());
//         }
//     }

//     void destroyEntity(Entity* entity)
//     {
//         // destroyPending.push_back(entity);
//         deleteEntity(entity);
//     }

//     std::vector<Entity*> findAll() const
//     {
//         std::vector<Entity*> result;
//         for (auto& e : entities) 
//         {
//             result.push_back(e.get());
//         }
//         return result;
//     }

//     template<typename... T>
//     std::vector<Entity*> findAll() const
//     {
//         std::vector<Entity*> result;
//         for (auto& e : entities) 
//         {
//             if ((e->hasComponent<T>() && ...)) 
//             {
//                 result.push_back(e.get());
//             }
//         }
//         return result;
//     }

//     template<typename... T>
//     Entity* findFirst() const
//     {
//         for (auto& e : entities) 
//         {
//             if ((e->hasComponent<T>() && ...)) 
//             {
//                 return e.get();
//             }
//         }
//         return nullptr;
//     }

//     template<typename T>
//     void addSystem()
//     {
//         // static_assert(std::is_base_of<System, T>::value, "T must inherit from System");

//         auto system = std::make_shared<T>();
//         systems[typeid(T)] = system;
//         orderedSystems.push_back(system);
//     }

//     template<typename T>
//     std::shared_ptr<T> getSystem() const
//     {
//         auto it = systems.find(typeid(T));
//         if (it == systems.end())
//         {
//             throw std::runtime_error("System not found");
//         }

//         return std::static_pointer_cast<T>(it->second);
//     }
    
//     void update(float deltaTime)
//     {
//         for (auto& system : orderedSystems)
//         {
//             system->preUpdate(*this, deltaTime);
//         }

//         for (auto& system : orderedSystems)
//         {
//             system->update(*this, deltaTime);
//         }

//         for (auto& system : orderedSystems)
//         {
//             system->postUpdate(*this, deltaTime);
//         }

//         for (Entity* entity : destroyPending)
//         {
//             deleteEntity(entity);
//         }

//         destroyPending.clear();
//     }

// private:
//     std::vector<std::unique_ptr<Entity>> entities;
//     std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
//     std::vector<std::shared_ptr<System>> orderedSystems;
//     std::vector<Entity*> destroyPending;
// };
