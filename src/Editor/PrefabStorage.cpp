#include <Editor/PrefabStorage.hpp>

#include <Entity/Enemy/Goomba.hpp>
#include <Entity/Enemy/Koopa.hpp>
#include <Entity/Enemy/KoopaFlying.hpp>
#include <Entity/Enemy/KoopaJumping.hpp>
#include <Entity/Enemy/Spiny.hpp>
#include <Entity/Enemy/Bowser.hpp>
#include <Entity/Enemy/Lakitu.hpp>

#include <Entity/Block/Block.hpp>

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
    prefabList[int(Category::Block)].emplace_back("CoinBlock",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<QuestionBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 1); // wrap raw pointer
        });
    
    // Mushroom Question block
    prefabList[int(Category::Block)].emplace_back("MushroomBlock",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<QuestionBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 2); // wrap raw pointer
        });

    // Flower Question block
    prefabList[int(Category::Block)].emplace_back("FlowerBlock",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<QuestionBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 3); // wrap raw pointer
        });

    // Star Question block
    prefabList[int(Category::Block)].emplace_back("StarBlock",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<QuestionBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f, 4); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Ground",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<GroundBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f); // wrap raw pointer
        });

    prefabList[int(Category::Block)].emplace_back("Stairs",
        [this](float x, float y) -> std::unique_ptr<Entity> {
            return std::make_unique<StairsBlock>(x / 3, y / 3, 16.0f, 16.0f, 3.0f); // wrap raw pointer
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