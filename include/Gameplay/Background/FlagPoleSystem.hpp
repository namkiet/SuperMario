#pragma once
#include <World.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Score/Components.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

class FlagPoleCollisionSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag>())
        {
            for (const auto &[collider, direction] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<FlagPole>())
                    continue;

                auto &pos = player->getComponent<Transform>().position;
                auto &size = player->getComponent<BoxCollider2D>().size;
                auto &flagPoleSize = collider->getComponent<BoxCollider2D>().size;
                auto &flagPolePos = collider->getComponent<Transform>().position;
                auto &velocity = player->getComponent<RigidBody>().velocity;

                // Check if the player has reached the flagpole

                if (direction != Direction::None)
                {
                    pos.x = flagPolePos.x - flagPoleSize.x / 2;
                    velocity.y = 200;
                    velocity.x = 0;
                }
            }
        }
    }
};