#pragma once
#include <Framework/EntityManager.hpp>
#include <Framework/SystemManager.hpp>
#include <Framework/ComponentRegistry.hpp>
#include <Framework/SaveManager.hpp>
#include <SFML/Graphics.hpp>

class World {
public:
    // === ENTITY MANAGEMENT ===
    Entity* createEntity() {
        return entityManager.createEntity();
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

    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        return systemManager.addSystem<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    std::shared_ptr<T> getSystem() const {
        return systemManager.getSystem<T>();
    }

    void update(float dt) {
        systemManager.updateAll(*this, dt);
    }

    // === SAVE / LOAD ===
    void loadSceneFromFile(const json& j) {
        saveManager.loadFromFile(j);
    }

    void saveSceneToFile(json& j) const{
        saveManager.saveToFile(j);
    }

    std::string saveGame(const json& j)
    {
        return saveManager.saveGame(j);
    }

public:
    World() : saveManager(entityManager, componentRegistry) {}

private:
    EntityManager entityManager;
    SystemManager systemManager;
    ComponentRegistry componentRegistry;
    SaveManager saveManager;

    friend class Editor;
    friend class GameManager;
};
