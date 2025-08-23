#pragma once

#include <algorithm>

#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Framework/World.hpp>

#include <Gameplay/Item/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/Player/Components.hpp>

class PatrolSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<PatrolComponent, BoxCollider2D, RigidBody>())
        {
            auto &patrol = entity->getComponent<PatrolComponent>();
            auto &rb = entity->getComponent<RigidBody>();

            for (const auto &[collider, direction, overlap] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (collider->hasComponent<PlayerTag>())
                    continue;
                if (collider->hasComponent<FireBulletTag>())
                    continue;
                if (collider->hasComponent<FireBarComponent>())
                    continue;
                if (collider->hasComponent<PodobooTag>())
                    continue;

                // If it collides with something on the left or on the right, it will reverse direction
                if ((direction == Direction::Left && patrol.isMovingRight) ||
                    (direction == Direction::Right && !patrol.isMovingRight))
                {
                    patrol.isMovingRight = !patrol.isMovingRight;
                    break;
                }
            }

            if (patrol.isMovingRight)
            {
                rb.velocity.x = abs(patrol.moveSpeed);
            }
            else
            {
                rb.velocity.x = -abs(patrol.moveSpeed);
            }
        }
    }
};