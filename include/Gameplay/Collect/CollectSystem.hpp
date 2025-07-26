#pragma once
#include <World.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Score/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

class CollectSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity *item : world.findAll<CollectableTag, Transform>())
        {
            for (const auto &[collider, direction] : item->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<CanCollectTag>())
                    continue;

                if (collider->hasComponent<ScoreComponent>())
                {
                    auto &scoreComponent = collider->getComponent<ScoreComponent>();
                    scoreComponent.score += 1000; // Increment score by 100 for each collectable item
                }

                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>();
                auto &textComponent = scoreTextEntity->getComponent<TextComponent>();
                textComponent.content = "1000"; // Example score text
                textComponent.x = item->getComponent<Transform>().position.x;
                textComponent.y = item->getComponent<Transform>().position.y - item->getComponent<Transform>().size.y / 2;
                
                // Check if the entity can collect the item
                item->addComponent<DespawnTag>();
            }
        }
    }
};