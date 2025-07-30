#pragma once
#include <World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <Gameplay/Player/Components.hpp>

class SlideOnFlagPoleSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity* player : world.findAll<SlidingOnFlagPoleTag, PlayerTag, BoxCollider2D, Transform>())
        {
            for (const auto &[block, direction] : player->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the player can capture the flag
                if (!block->hasComponent<BlockTag>()) continue;
                if (direction != Direction::Top) continue;

                auto& playerPos = player->getComponent<Transform>().position;
                auto& playerBox = player->getComponent<BoxCollider2D>();

                playerPos.x += playerBox.size.x;
                player->addComponent<FlipXTag>();

                player->removeComponent<SlidingOnFlagPoleTag>();
                player->getComponent<RigidBody>().velocity.x = 300.0f;
            }
        }
    }
};