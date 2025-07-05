#pragma once

#include <ECS/Component.hpp>
#include <typeindex>
#include <memory>
#include <unordered_map>

class Entity 
{
public:
    virtual ~Entity() = default;
    
    template<typename T, typename... Args>
    void addComponent(Args&&... args) 
    {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void removeComponent() 
    {
        components.erase(typeid(T));
    }

    template<typename T>
    bool hasComponent() const 
    {
        return components.find(typeid(T)) != components.end();
    }

    template<typename T>
    T& getComponent() 
    {
        auto it = components.find(typeid(T));
        // assert(it != components.end() && "Component not found");
        return *static_cast<T*>(it->second.get());
    }
    
    // Entity clone() const
    // {
    //     Entity newEntity;

    // }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};