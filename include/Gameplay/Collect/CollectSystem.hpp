#pragma once
#include <Framework/World.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <CoinManager.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <ScoreManager.hpp>

class CollectSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity *item : world.findAll<CollectableTag, BoxCollider2D>())
        {
            for (const auto &[collider, direction, overlap] : item->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the entity can collect the item
                if (!collider->hasComponent<CanCollectTag>())
                    continue;

                if (item->hasComponent<LevelMushroomTag>())
                    continue; // Don't score level mushrooms

                if (!item->hasComponent<Coin2Tag>())
                    ScoreManager::instance().addScore(1000);

                else
                {
                    ScoreManager::instance().addScore(200);
                    world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/coin.wav"));
                }

                if (!item->hasComponent<Coin2Tag>())
                {
                    Entity *scoreTextEntity = world.createEntity();
                    float x = item->getComponent<Transform>().position.x;
                    float y = item->getComponent<Transform>().position.y - item->getComponent<Transform>().size.y / 2;
                    scoreTextEntity->addComponent<TextComponent>("1000", x, y, y - 48, 15.0f, 1);
                }

                CoinManager::instance().addCoin();

                item->addComponent<DespawnTag>();
            }
        }
    }
};