#pragma once
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "ComponentRegistry.hpp"
#include "SaveManager.hpp"

class World {
public:
    // === ENTITY MANAGEMENT ===
    Entity* createEntity() {
        return entityManager.createEntity();
    }

    Entity* createEntity(int id) {
        return entityManager.createEntity(id);
    }

    template<typename T, typename... Args>
    Entity* createEntity(Args&&... args) {
        return entityManager.createEntity<T>(std::forward<Args>(args)...);
    }

    void destroyEntity(Entity* entity) {
        entityManager.destroyEntity(entity);
    }

    void removeAllEntities() {
        entityManager.removeAllEntities();
    }

    Entity* getEntityByID(int id) {
        return entityManager.getEntityByID(id);
    }

    std::vector<Entity*> findAll() const {
        return entityManager.findAll();
    }

    template<typename... T>
    std::vector<Entity*> findAll() const {
        return entityManager.findAll<T...>();
    }

    template<typename... T>
    Entity* findFirst() const {
        return entityManager.findFirst<T...>();
    }

    // === SYSTEM MANAGEMENT ===
    template<typename T>
    void addSystem() {
        systemManager.addSystem<T>();
    }

    template<typename T>
    std::shared_ptr<T> getSystem() const {
        return systemManager.getSystem<T>();
    }

    void update(float dt) {
        systemManager.updateAll(*this, dt);
    }

    // === SAVE / LOAD ===
    void loadSceneFromFile(const std::string& filename) {
        saveManager.loadFromFile(filename);
    }

    void saveSceneToFile(const std::string& filename) {
        saveManager.saveToFile(filename);
    }

public:
    World() : saveManager(entityManager, componentRegistry) {}

private:
    EntityManager entityManager;
    SystemManager systemManager;
    ComponentRegistry componentRegistry;
    SaveManager saveManager;
};
