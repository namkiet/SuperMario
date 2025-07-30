#pragma once
#include <World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <Gameplay/Player/Components.hpp>

class CaptureFlagSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity* player : world.findAll<CanCaptureFlagTag, PlayerTag, BoxCollider2D, Transform>())
        {
            for (const auto &[flag, _] : player->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the player can capture the flag
                if (!flag->hasComponent<FlagPoleTag>()) continue;
                if (!flag->hasComponent<Transform>()) continue;
                if (!flag->hasComponent<BoxCollider2D>()) continue;

                auto& playerPos = player->getComponent<Transform>().position;
                auto& playerBox = player->getComponent<BoxCollider2D>();

                auto& flagPos = flag->getComponent<Transform>().position;
                auto& flagBox = flag->getComponent<BoxCollider2D>();

                playerPos.x = flagPos.x + flagBox.offset.x + 0.5f * flagBox.size.x - playerBox.offset.x - playerBox.size.x;

                player->removeComponent<InputTag>();
                player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 100);
                player->addComponent<SlidingOnFlagPoleTag>();

                return;
            }
        }
    }
};