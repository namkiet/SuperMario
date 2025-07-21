#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>

class CoinJumpingSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *coin : world.findAll<Coin1Tag, Transform>())
        {
            auto &pos = coin->getComponent<Transform>().position;
            auto &size = coin->getComponent<Transform>().size;

            // Make the coin jump
            pos.y -= 100.0f * dt; // Adjust the jump height and speed as needed

            // Reset position after jumping
            if (pos.y < -size.y)
            {
                pos.y = 600.0f; // Reset to a specific height
            }
        }
    }
};