#pragma once

#include <ECS/Component.hpp>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class Entity 
{
public:
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
        if (it == components.end())
        {
            std::string error = "Cannot find Component " + std::string(typeid(T).name()) + " of Entity " + name + " " + std::to_string(id);
            throw std::runtime_error(error);
        }
        return *static_cast<T*>(it->second.get());
    }

public:
    Entity() 
        : id(generateID()), name("Unknown") {}

    explicit Entity(int givenID, const std::string& name) 
        : id(assignSpecificID(givenID)), name(name) {}

    virtual ~Entity() { releaseID(id); }

    int getID() const { return id; }

    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

private:
    int id;
    std::string name;

    static int generateID() 
    {
        if (!freeIDs.empty()) {
            int reusedID = freeIDs.back();
            freeIDs.pop_back();
            return reusedID;
        }
        return ++counter;
    }

    static int assignSpecificID(int givenID) 
    {
        // Remove from free list if it’s there (optional)
        auto it = std::find(freeIDs.begin(), freeIDs.end(), givenID);
        if (it != freeIDs.end()) {
            freeIDs.erase(it);
        }
        // Keep counter in sync so future auto IDs are correct
        if (givenID > counter) {
            counter = givenID;
        }
        return givenID;
    }

    static void releaseID(int releasedID) 
    {
        freeIDs.push_back(releasedID);
    }

    static inline int counter{0};
    static inline std::vector<int> freeIDs;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};