#pragma once
#include <World.hpp>
#include <Components/PlayerTag.hpp>
#include <Components/EnemyTag.hpp>
#include <Core/Physics.hpp>

class PlayerEnemyCollisionSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        auto players = world.findAll<PlayerTag, Transform, BoxCollider2D, RigidBody>();
        auto enemies = world.findAll<EnemyTag, Transform, BoxCollider2D>();

        for (Entity* player : players) 
        {
            auto& tfP = player->getComponent<Transform>();
            auto& boxP = player->getComponent<BoxCollider2D>();
            auto& rbP = player->getComponent<RigidBody>();

            for (Entity* enemy : enemies) {
                auto& tfE = enemy->getComponent<Transform>();
                auto& boxE = enemy->getComponent<BoxCollider2D>();

                auto info = Physics::AABBOverlap2(player, enemy);
                if (info.direction == Physics::CollisionDirection::None) continue;

                if (info.direction == Physics::CollisionDirection::Top)
                {
                    // Small bounce when stomping the enemy
                    enemy->addComponent<DeadTag>();
                    tfP.position.y -= 10.0f;
                    rbP.velocity.y = -500.0f;
                }
                else
                {
                    player->addComponent<DeadTag>();
                }
            }
        }
    }
};
