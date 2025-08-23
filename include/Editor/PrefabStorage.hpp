#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <Engine/Animation/Animation.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>

#include <Entity/Enemy/Goomba.hpp>
#include <Entity/Enemy/Koopa.hpp>
#include <Entity/Enemy/KoopaFlying.hpp>
#include <Entity/Enemy/KoopaJumping.hpp>
#include <Entity/Enemy/Spiny.hpp>
#include <Entity/Enemy/Bowser.hpp>
#include <Entity/Block/Block.hpp>

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
    PrefabStorage(EntityManager& em, ComponentRegistry& cr) : em(em), cr(cr) { registerPrefabs(); }

    const std::vector<Prefab>& getAll() const { return prefabList; }
    std::vector<Prefab>& getAll() { return prefabList; }

private:
    std::vector<Prefab> prefabList;
    EntityManager& em;
    ComponentRegistry& cr;

    void registerPrefabs()
    {
        registerEnemies();
        registerBlocks();
        registerItems();
    }

    void registerEnemies()
    {
        // Goomba
        prefabList.emplace_back("Goomba",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Goomba>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });

        // Koopa
        prefabList.emplace_back("Koopa",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Koopa>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });
        
        // KoopaJumping
        prefabList.emplace_back("KoopaJumping",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<KoopaJumping>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });

        // KoopaFlying
        prefabList.emplace_back("KoopaFlying",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<KoopaFlying>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });

        // Spiny
        prefabList.emplace_back("Spiny",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Spiny>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });

        // Bowser
        prefabList.emplace_back("Bowser",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Bowser>(x / 3, y / 3, 3.0f); // wrap raw pointer
            });
    }
    
    void registerBlocks()
    {
        // Coin Question block
        prefabList.emplace_back("Coin",
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Block>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 1); // wrap raw pointer
            });

        
    }

    void registerItems()
    {
        
    }
};
