#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <Engine/Animation/Animation.hpp>
#include <Framework/EntityManager.hpp>
#include <Framework/ComponentRegistry.hpp>

#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>

struct Prefab
{
    using CreatorFunc = std::function<std::unique_ptr<Entity>(float, float)>;

    std::string name;
    Animation animation;                     
    sf::Vector2f size;                        
    CreatorFunc creator; // Creates an entity at x,y

    Prefab(const std::string& name_, const Animation& anim, CreatorFunc creatorFunc)
        : name(name_), animation(anim), creator(std::move(creatorFunc))
    {
        size = creator(0, 0)->getComponent<Transform>().size;
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
        // Goomba
        Animation goombaAnim(TextureManager::load("assets/Enemy/Goomba/goomba_walk.png"), 16, 16, 2, 0.25f);
        sf::Vector2f goombaSize{16.f, 16.f};
        prefabList.emplace_back("Goomba", goombaAnim,
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Goomba>(x / 3, y / 3, 3); // wrap raw pointer
            });

        // Koopa
        Animation koopaAnim(TextureManager::load("assets/Enemy/Koopa/koopa_walk.png"), 16, 24, 2, 0.25f);
        sf::Vector2f koopaSize{16.f, 24.f};
        prefabList.emplace_back("Koopa", koopaAnim,
            [this](float x, float y) -> std::unique_ptr<Entity> {
                return std::make_unique<Koopa>(x / 3, y / 3, 3); // wrap raw pointer
            });
    }
};
