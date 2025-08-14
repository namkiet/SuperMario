#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <iostream>

class CoinJumpingSystem : public System
{
private:
public:
    void update(World &world, float dt) override
    {
        for (Entity *coin : world.findAll<Coin1Tag, Transform, LifeSpan>())
        {
            auto &pos = coin->getComponent<Transform>().position;
            auto &size = coin->getComponent<Transform>().size;
            auto &lifeSpan = coin->getComponent<LifeSpan>();

            // Make the coin jump
            pos.y -= 100.0f * dt; // Adjust the jump height and speed as needed

            if (lifeSpan.value <= 0.0f)
            {
                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y + size.y, pos.y + size.y - 48, 15, 1);
                world.getScoreManager().addScore(200);
            }
        }
    }
};