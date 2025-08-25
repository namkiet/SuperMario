#include <Editor/PrefabStorage.hpp>

#include <Entity/Enemy/Goomba.hpp>
#include <Entity/Enemy/Koopa.hpp>
#include <Entity/Enemy/KoopaFlying.hpp>
#include <Entity/Enemy/KoopaJumping.hpp>
#include <Entity/Enemy/Spiny.hpp>
#include <Entity/Enemy/Bowser.hpp>
#include <Entity/Enemy/Lakitu.hpp>

#include <Entity/Block/Block.hpp>
#include <Entity/Block/Pipe.hpp>

#include <Entity/Miscellaneous/Background.hpp>
#include <Entity/Miscellaneous/Bridge.hpp>

#include <Entity/Item/Coin.hpp>
#include <Entity/Item/Flower.hpp>
#include <Entity/Item/Mushroom.hpp>
#include <Entity/Item/Star.hpp>

#include <Gameplay/Item/ItemEmerging.hpp>

void PrefabStorage::registerEnemies()
{
    // Goomba
    prefabList[int(Category::Enemy)].emplace_back("Goomba",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Goomba>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });

    // Koopa
    prefabList[int(Category::Enemy)].emplace_back("Koopa",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Koopa>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });
    
    // KoopaJumping
    prefabList[int(Category::Enemy)].emplace_back("KoopaJumping",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<KoopaJumping>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });

    // KoopaFlying
    prefabList[int(Category::Enemy)].emplace_back("KoopaFlying",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<KoopaFlying>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });

    // Spiny
    prefabList[int(Category::Enemy)].emplace_back("Spiny",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Spiny>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });

    // Bowser
    prefabList[int(Category::Enemy)].emplace_back("Bowser",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Bowser>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });

    // Lakitu
    prefabList[int(Category::Enemy)].emplace_back("Lakitu",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Lakitu>(x / 3, y / 3, 3.0f); // wrap raw pointer
        });
}

void PrefabStorage::registerBlocks()
{
    // Coin Question block
    prefabList[int(Category::Block)].emplace_back("Coin Block",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<QuestionBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 1); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Ground",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<GroundBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Stairs",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<StairsBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Pipe 0",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Pipe>(x / 3, y / 3, 32.0f, 16.0f, 3.0f, 0, false); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Pipe 1",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Pipe>(x / 3, y / 3, 32.0f, 16.0f, 3.0f, 1, false); // wrap raw pointer
        });


    prefabList[int(Category::Block)].emplace_back("Pipe 2",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Pipe>(x / 3, y / 3, 32.0f, 16.0f, 3.0f, 2, false); // wrap raw pointer
        });
}

void PrefabStorage::registerItems()
{
    prefabList[int(Category::Item)].emplace_back("Coin",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Coin2>(x / 3, y / 3, 16.0f, 16.0f, 3.0f); // wrap raw pointer
        });

    prefabList[int(Category::Item)].emplace_back("Flower",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            auto e = std::make_unique<Flower>(x, y, 48.0f, 48.0f); // wrap raw pointer
            e->addComponent<ItemEmerging>(true);
            return std::move(e);
        });

    prefabList[int(Category::Item)].emplace_back("Star",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            auto e = std::make_unique<Star>(x, y, 48.0f, 48.0f); // wrap raw pointer
            e->addComponent<ItemEmerging>(true);
            return std::move(e);
        });

    prefabList[int(Category::Item)].emplace_back("Mushroom",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            auto e = std::make_unique<Mushroom1>(x, y, 48.0f, 48.0f); // wrap raw pointer
            e->addComponent<ItemEmerging>(true);
            return std::move(e);
        });
}


void PrefabStorage::registerBackgrounds()
{
    prefabList[int(Category::Background)].emplace_back("Castle",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Background>(x / 3, y / 3, 80.0f, 80.0f, 3, 0); // wrap raw pointer
        });

    prefabList[int(Category::Background)].emplace_back("Bridge 1",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Bridge>(x / 3, y / 3, 3, 1); // wrap raw pointer
        });

    prefabList[int(Category::Background)].emplace_back("Bridge 2",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<Bridge>(x / 3, y / 3, 3, 2); // wrap raw pointer
        });
}