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

                // For score
                if (player->hasComponent<ScoreComponent>())
                {
                    auto &timeComponent = player->getComponent<TimeComponent>();

                    if (timeComponent.firstTimePause)
                        continue;
                    auto &scoreComponent = player->getComponent<ScoreComponent>();

                    Entity *scoreTextEntity = world.createEntity();
                    float x = flagPolePos.x + flagPoleSize.x / 2 + 10;
                    float y = flagPolePos.y + flagPoleSize.y;

                    if (pos.y <= flagPolePos.y)
                    {
                        scoreComponent.score += 5000;
                        scoreTextEntity->addComponent<TextComponent>("5000", x, y, 30, 15, 25);
                    }
                    else if (pos.y > flagPolePos.y && pos.y <= flagPolePos.y + flagPoleSize.y)
                    {
                        scoreComponent.score += 800; // Increment score by 100
                        scoreTextEntity->addComponent<TextComponent>("800", x, y, 30, 15, 25);
                    }
                    else
                    {
                        scoreComponent.score += 100; // Increment score by 100
                        scoreTextEntity->addComponent<TextComponent>("100", x, y, 30, 15, 25);
                    }
                    timeComponent.firstTimePause = true;
                }

                Entity *flag = nullptr;
                for (Entity *entity : world.findAll<Flag>())
                {
                    flag = entity;
                    break;
                }

                if (flag)
                {
                    flag->addComponent<RigidBody>(sf::Vector2f(0, 200));
                }
            }
        }
    }
};