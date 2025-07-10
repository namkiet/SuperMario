#pragma once
#include <World.hpp>
#include <Components/EnemyTag.hpp>
#include <Components/RigidBody.hpp>
#include <algorithm>

class EnemyAISystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* enemy : world.findAll<EnemyTag, EnemyAI, RigidBody>())
        {
            auto& ai = enemy->getComponent<EnemyAI>();
            auto& rb = enemy->getComponent<RigidBody>();
            
            if (rb.velocity.x == 0.0f)
            {
                ai.isMovingRight = !ai.isMovingRight;
            }

            rb.velocity.x = ai.moveSpeed * (ai.isMovingRight ? 1 : -1);
        }
    }
};