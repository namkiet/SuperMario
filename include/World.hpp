#pragma once
#include <ECS/Entity.hpp>
#include <ECS/System.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <typeindex>

class World {
public:
    Entity* createEntity() 
    {
        entities.push_back(std::make_unique<Entity>());
        return entities.back().get();
    }

    Entity* createEntity(std::unique_ptr<Entity> entity)
    {
        entities.push_back(std::move(entity));
        return entities.back().get();
    }

    std::vector<Entity*> findAll() const
    {
        std::vector<Entity*> result;
        for (auto& e : entities) 
        {
            result.push_back(e.get());
        }
        return result;
    }

    template<typename... T>
    std::vector<Entity*> findAll() const
    {
        std::vector<Entity*> result;
        for (auto& e : entities) 
        {
            if ((e->hasComponent<T>() && ...)) 
            {
                result.push_back(e.get());
            }
        }
        return result;
    }

    template<typename... T>
    Entity* findFirst() const
    {
        for (auto& e : entities) 
        {
            if ((e->hasComponent<T>() && ...)) 
            {
                return e.get();
            }
        }
        return nullptr;
    }

    template<typename T>
    void addSystem()
    {
        // static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
        systems[typeid(T)] = std::make_shared<T>();
    }

    template<typename T>
    std::shared_ptr<T> getSystem() const
    {
        // static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
        auto it = systems.find(typeid(T));
        if (it == systems.end()) 
        {
            throw std::runtime_error("System not found");
        }
        return std::static_pointer_cast<T>(it->second);
    }
    
    void update(float deltaTime) 
    {
        for (auto& [id, system] : systems) 
        {
            system->update(*this, deltaTime);
        }
    }


private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
};
