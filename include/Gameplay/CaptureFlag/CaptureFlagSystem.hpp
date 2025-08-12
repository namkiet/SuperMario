#pragma once
#include <Framework/World.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>

class CaptureFlagSystem : public System
{
private:
    void checkCollisionWithFlagPole(World& world, float dt)
    {
        for (Entity* player : world.findAll<CanCaptureFlagTag, PlayerTag, BoxCollider2D, Transform>())
        {

            for (auto &[pole, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!pole->hasComponent<FlagPoleTag>()) continue;
                if (!pole->hasComponent<Transform>()) continue;
                if (!pole->hasComponent<BoxCollider2D>()) continue;

                auto& playerPos = player->getComponent<Transform>().position;
                auto& playerBox = player->getComponent<BoxCollider2D>();
                auto& flagPos = pole->getComponent<Transform>().position;
                auto& flagSize = pole->getComponent<BoxCollider2D>().size;

                // Check if the player has reached the flagpole
                // playerPos.x = flagPos.x - flagSize.x / 2;

                player->removeComponent<CanCaptureFlagTag>();
                player->removeComponent<InputTag>();
                player->addComponent<RigidBody>(sf::Vector2f(0, 200), false);

                // pull the flag down
                if (auto flag = world.findFirst<Flag>())
                {
                    flag->addComponent<RigidBody>(sf::Vector2f(0, 300), false);
                }

                player->addComponent<SlidingOnFlagPoleTag>();

                // continue;
                // auto &pos = player->getComponent<Transform>().position;
                // auto &size = player->getComponent<BoxCollider2D>().size;
                // auto &flagSize = collider->getComponent<BoxCollider2D>().size;
                // auto &flagPos = collider->getComponent<Transform>().position;
                // auto &velocity = player->getComponent<RigidBody>().velocity;

                // // Check if the player has reached the flagpole
                playerPos.x = flagPos.x + flagSize.x / 2 - playerBox.size.x;

                // velocity.y = 200;
                // velocity.x = 0;
                // // std::cout << "Player reached the flagpole!" << std::endl;

                if (player->hasComponent<TimeComponent>())
                {
                    auto &timeComponent = player->getComponent<TimeComponent>();
                    if (!timeComponent.isPaused)
                    {
                        timeComponent.timeUnitLeft = timeComponent.timer % 10; // Store the remaining time unit
                        timeComponent.isPaused = true;
                    }
                    // Pause the timer when reaching the flagpole
                }

                // Entity *flag = nullptr;
                // for (Entity *entity : world.findAll<Flag>())
                // {
                //     flag = entity;
                //     break;
                // }

                // if (flag)
                // {
                //     if (!flag->hasComponent<RigidBody>())
                //     {
                //         flag->addComponent<RigidBody>(sf::Vector2f(0, 300));
                //     }
                //     else
                //     {
                //         flag->getComponent<RigidBody>().velocity = sf::Vector2f(0, 300);
                //     }
                // }

                // // For score
                if (player->hasComponent<ScoreComponent>())
                {
                    auto &timeComponent = player->getComponent<TimeComponent>();

                    if (timeComponent.firstTimePause)
                        continue;
                    auto &scoreComponent = player->getComponent<ScoreComponent>();

                    Entity *scoreTextEntity = world.createEntity();
                    float x = flagPos.x + flagSize.x / 2 + 10;
                    float y = flagPos.y + flagSize.y;

                    if (playerPos.y <= flagPos.y)
                    {
                        scoreComponent.score += 5000;
                        scoreTextEntity->addComponent<TextComponent>("5000", x, y, flagPos.y + 48, 25, 2);
                    }
                    else if (playerPos.y > flagPos.y && playerPos.y <= flagPos.y + flagSize.y)
                    {
                        scoreComponent.score += 800; // Increment score by 100
                        scoreTextEntity->addComponent<TextComponent>("800", x, y, flagPos.y + 48, 25, 2);
                    }
                    else
                    {
                        scoreComponent.score += 100; // Increment score by 100
                        scoreTextEntity->addComponent<TextComponent>("100", x, y, flagPos.y + 48, 25, 2);
                    }
                    timeComponent.firstTimePause = true;
                }
            }
        }
    }

    void checkCollisionWithFlagBlock(World& world, float dt)
    {
        for (Entity* player : world.findAll<SlidingOnFlagPoleTag, PlayerTag, BoxCollider2D, Transform>())
        {
            for (auto &[block, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<FlagBlock>()) continue;
                if (!block->hasComponent<BoxCollider2D>()) continue;

                auto& pos = player->getComponent<Transform>().position;
                auto& box = player->getComponent<BoxCollider2D>();
                pos.x += box.size.x;

                player->addComponent<FlipXTag>();
                player->addComponent<HoldingTimer>(0.25f);
                player->removeComponent<SlidingOnFlagPoleTag>();
            }
        }
    }

    void goRight(World& world, float dt)
    {
        for (Entity* player : world.findAll<PlayerTag, HoldingTimer>())
        {
            auto& duration = player->getComponent<HoldingTimer>().duration;
            duration -= dt;
            if (duration < 0.0f)
            {
                player->addComponent<RigidBody>(sf::Vector2f(200, 0));
                player->removeComponent<HoldingTimer>();
            }
        }
    }

public:
    void update(World &world, float dt) override
    {
        checkCollisionWithFlagPole(world, dt);
        checkCollisionWithFlagBlock(world, dt);
        goRight(world, dt);
    }
};