#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Score/Components.hpp>
#include <iostream>

class CoinJumpingSystem : public System
{
private:
    int count = 0;

public:
    void update(World &world, float dt) override
    {
        for (Entity *coin : world.findAll<Coin1Tag, Transform>())
        {
            ++count;
            auto &pos = coin->getComponent<Transform>().position;
            auto &size = coin->getComponent<Transform>().size;

            // Make the coin jump
            pos.y -= 100.0f * dt; // Adjust the jump height and speed as needed

            if (count % 14 == 0)
            {
                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>();
                auto &textComponent = scoreTextEntity->getComponent<TextComponent>();
                textComponent.content = "200"; // Example score text
                textComponent.x = pos.x;
                textComponent.y = pos.y + size.y;
                count = 0; // Reset count after displaying score

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

                        // Reset position after jumping
            // if (pos.y < coin->getComponent<CoinComponent>())
            // {
            //     cout << "Coin jumped and reset position." << endl;
            //     pos.y = 600.0f; // Reset to a specific height
            // }
        }
    }
};