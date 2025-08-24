#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>

#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>

struct Prefab
{
    using CreatorFunc = std::function<std::unique_ptr<Entity>(float, float)>;

    std::string name;
    Animation animation;                     
    sf::Vector2f size;                        
    CreatorFunc creator; // Creates an entity at x,y
    sf::Vector2f curPos;
    bool canBePlaced = true;

    Prefab(const std::string& name_, CreatorFunc creatorFunc)
        : name(name_), creator(std::move(creatorFunc))
    {
        auto sample = creator(0, 0);
        if (sample->hasComponent<Transform>())
        {
            size = creator(0, 0)->getComponent<Transform>().size;
        }

        if (sample->hasComponent<Animation>())
        {
            animation = creator(0, 0)->getComponent<Animation>();
        }
    }
};

class PrefabStorage
{
public:
    enum class Category { Block, Item, Enemy, Background };

    PrefabStorage(EntityManager& em, ComponentRegistry& cr) : em(em), cr(cr) { registerPrefabs(); }

    const std::vector<Prefab>& getCategory(Category c) const { return prefabList.at(int(c)); }
    std::vector<Prefab>& getCategory(Category c) { return prefabList.at(int(c)); }

private:
    std::unordered_map<int, std::vector<Prefab>> prefabList;
    EntityManager& em;
    ComponentRegistry& cr;

    void registerPrefabs()
    {
        registerEnemies();
        registerBlocks();
        registerItems();
        registerBackgrounds();
    }

    void registerEnemies();
    void registerBlocks();
    void registerItems();
    void registerBackgrounds();
};
