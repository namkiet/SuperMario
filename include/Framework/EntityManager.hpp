#pragma once
#include <ECS/Entity.hpp>
#include <memory>
#include <vector>
#include <algorithm>

class EntityManager {
public:
    ~EntityManager() { entities.clear(); }

    Entity* createEntity() {
        entities.push_back(std::make_unique<Entity>());
        return entities.back().get();
    }

    Entity* createEntity(int id) {
        entities.push_back(std::make_unique<Entity>(id));
        return entities.back().get();
    }

    template<typename T, typename... Args>
    Entity* createEntity(Args&&... args) {
        entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return entities.back().get();
    }

    void destroyEntity(Entity* entity) {
        auto it = std::remove_if(entities.begin(), entities.end(),
            [entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; });
        entities.erase(it, entities.end());
    }

    void removeAllEntities() {
        entities.clear();
    }

    std::vector<Entity*> findAll() const {
        std::vector<Entity*> result;
        for (auto& e : entities) result.push_back(e.get());
        return result;
    }

    template<typename... T>
    std::vector<Entity*> findAll() const {
        std::vector<Entity*> result;
        for (auto& e : entities) {
            if ((e->hasComponent<T>() && ...)) result.push_back(e.get());
        }
        return result;
    }

    template<typename... T>
    Entity* findFirst() const {
        for (auto& e : entities) {
            if ((e->hasComponent<T>() && ...)) return e.get();
        }
        return nullptr;
    }

    static Entity* getEntityByID(int id) {
        for (auto& e : entities) {
            if (e->getID() == id) return e.get();
        }
        return nullptr;
    }

private:
    static inline std::vector<std::unique_ptr<Entity>> entities;
};
