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
        for (Entity *item : world.findAll<CollectableTag, BoxCollider2D>())
        {
            for (const auto &[collider, direction] : item->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the entity can collect the item
                if (!collider->hasComponent<CanCollectTag>()) continue;

                if (collider->hasComponent<ScoreComponent>())
                {
                    auto &scoreComponent = collider->getComponent<ScoreComponent>();
                    scoreComponent.score += 100; // Increment score by 100 for each collectable item
                }
                item->addComponent<DespawnTag>();
            }
        }
    }
};