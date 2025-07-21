#pragma once
#include <World.hpp>
#include <Gameplay/Collect/Components.hpp>
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

                // Check if the entity can collect the item
                item->addComponent<DespawnTag>();
            }
        }
    }
};