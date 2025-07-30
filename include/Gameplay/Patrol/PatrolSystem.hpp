#pragma once
#include <World.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <algorithm>

class PatrolSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<PatrolComponent, BoxCollider2D, RigidBody>())
        {
            auto& patrol = entity->getComponent<PatrolComponent>();
            auto& rb = entity->getComponent<RigidBody>();
            
            for (const auto& [collider, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (collider->hasComponent<PlayerTag>())
                    continue;
                if (collider->hasComponent<FireBulletTag>())
                    continue;
                // If it collides with something on the left or on the right, it will reverse direction
                if (direction == Direction::Left || direction == Direction::Right)
                {
                    patrol.isMovingRight = !patrol.isMovingRight;
                    break;
                }
            }

            rb.velocity.x = patrol.moveSpeed * (patrol.isMovingRight ? 1 : -1);
        }
    }
};