#pragma once
#include <World.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

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

                Entity *gameSession = world.findFirst<CoinComponent>();
                if (!gameSession)
                    continue;
                auto &coinComponent = gameSession->getComponent<CoinComponent>();

                if (!item->hasComponent<Coin2Tag>())
                    world.getScoreManager().addScore(1000);

                else
                    world.getScoreManager().addScore(200);

                if (!item->hasComponent<Coin2Tag>())
                {
                    Entity *scoreTextEntity = world.createEntity();
                    float x = item->getComponent<Transform>().position.x;
                    float y = item->getComponent<Transform>().position.y - item->getComponent<Transform>().size.y / 2;
                    scoreTextEntity->addComponent<TextComponent>("1000", x, y, y - 48, 15, 1);
                }
                ++coinComponent.coins;
                
                item->addComponent<DespawnTag>();
            }
        }
    }
};