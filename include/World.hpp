#pragma once
#include <ECS/Entity.hpp>
#include <ECS/System.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <algorithm>

#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <iostream>
class World
{
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
        int i = 0;
        for (auto &system : orderedSystems)
        {
            i += 1;
            system->update(*this, deltaTime);
            auto player = findFirst<PlayerTag>();
            if (!player) continue;
            auto rb = player->getComponent<RigidBody>();
            std::cout << i <<" rb.velocity.y = " << rb.velocity.y << std::endl;
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

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::vector<std::shared_ptr<System>> orderedSystems;
    std::vector<Entity *> destroyPending;
};
