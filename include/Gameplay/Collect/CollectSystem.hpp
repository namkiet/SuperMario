#pragma once
#include <World.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Score/Components.hpp>
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

                if (collider->hasComponent<ScoreComponent>())
                {
                    auto &scoreComponent = collider->getComponent<ScoreComponent>();
                    if (!item->hasComponent<Coin2Tag>())
                        scoreComponent.score += 1000; // Increment score by 100 for each collectable item}
                    else
                        scoreComponent.score += 200; // Increment score by 2000 for Coin2
                }

                if (!item->hasComponent<Coin2Tag>())
                {
                    Entity *scoreTextEntity = world.createEntity();
                    float x = item->getComponent<Transform>().position.x;
                    float y = item->getComponent<Transform>().position.y - item->getComponent<Transform>().size.y / 2;
                    scoreTextEntity->addComponent<TextComponent>("1000", x, y, y - 48, 15, 1);
                }
                if (collider->hasComponent<CoinComponent>())
                {
                    auto &coinComp = collider->getComponent<CoinComponent>();
                    ++coinComp.coins; // Increment coins
                }
                item->addComponent<DespawnTag>();
            }
        }
    }
};