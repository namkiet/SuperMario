#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Score/Components.hpp>
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

            if (lifeSpan.value <= dt)
            {
                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y + size.y, 15, 15,5);

                Entity *player = nullptr;
                for (Entity *entity : world.findAll<PlayerTag>())
                {
                    if (entity->hasComponent<ScoreComponent>())
                    {
                        player = entity;
                        break;
                    }
                }

                if (player)
                {
                    auto &scoreComp = player->getComponent<ScoreComponent>();
                    scoreComp.score += 200; // Increment score by 100
                }
            }
        }
    }
};