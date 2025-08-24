#pragma once
#include <ECS/System.hpp>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <stdexcept>

class SystemManager {
public:
    template<typename T>
    void addSystem() {
        auto system = std::make_shared<T>();
        systems[typeid(T)] = system;
        orderedSystems.push_back(system);
    }

    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        systems[typeid(T)] = system;
        orderedSystems.push_back(system);
    }

    template<typename T>
    std::shared_ptr<T> getSystem() const {
        auto it = systems.find(typeid(T));
        if (it == systems.end()) throw std::runtime_error("System not found");
        return std::static_pointer_cast<T>(it->second);
    }

    void updateAll(World& world, float dt) {
        for (auto& s : orderedSystems) s->preUpdate(world, dt);
        for (auto& s : orderedSystems) s->update(world, dt);
        for (auto& s : orderedSystems) s->postUpdate(world, dt);
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::vector<std::shared_ptr<System>> orderedSystems;
};
