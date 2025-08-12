#pragma once
#include <Framework/World.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Prefabs/Fireworks.hpp>
#include <Prefabs/Background.hpp>
#include <iostream>

class LevelCompletionSystem : public System
{
private:
    void castleCollisionCheck(World &world, float dt, Entity *player, Entity *collider)
    {
        auto &castlePos = collider->getComponent<Transform>().position;
        auto &castleSize = collider->getComponent<Transform>().size;

        // Check if the player has reached the flagpole

        if (player->hasComponent<Animation>())
            player->removeComponent<Animation>();
        player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);

        // Make the timer go faster
        auto &timeComponent = player->getComponent<TimeComponent>();
        auto &scoreComponent = player->getComponent<ScoreComponent>();
        timeComponent.goesFaster = true;
        if (timeComponent.timer > 0)
        {
            scoreComponent.score += 50; // Increment score by 100
        }

        if (timeComponent.timer <= 0 && !timeComponent.firstTimeReach0)
        {
            float x = (castlePos.x + 48 * 2) / 3;
            float y = (castlePos.y) / 3;
            auto castleFlag = world.createEntity<Background>(x, y, 14.0f, 14.0f, 3, 11);
            ItemEmerging emerging;
            emerging.finalY = castlePos.y - 14 * 3;
            castleFlag->addComponent<ItemEmerging>(emerging);
            timeComponent.firstTimeReach0 = true;
            // std::cout << "Castle flag is trigger to create" << std::endl;
        }

        Entity *flag = world.findFirst<CastleFlag>();

        if (flag)
        {
            if (!player->hasComponent<FireworkComponent>())
            {
                auto timeComponent = player->getComponent<TimeComponent>();
                int n = timeComponent.timeUnitLeft;
                if (n == 1 || n == 3 || n == 6)
                {
                    player->addComponent<FireworkComponent>(n);
                }
            }
            // Spawn one firework at a time
            else
            {
                auto &seq = player->getComponent<FireworkComponent>();
                if (seq.fireworksLeft > 0 && Fireworks::getFireworksCount() < 1)
                {
                    world.createEntity<Fireworks>(48.0f, 48.0f);
                    if (player->hasComponent<ScoreComponent>())
                    {
                        auto &scoreComponent = player->getComponent<ScoreComponent>();
                        scoreComponent.score += 100; // Increment score by 100
                    }
                    --seq.fireworksLeft;
                }
            }
        }
    }
    void princessCollisionCheck(World &world, float dt, Entity *player)
    {
        player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);
    }

public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D, RigidBody, TimeComponent, ScoreComponent>())
        {
            for (const auto &[collider, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<Transform>())
                    continue;

                if (collider->hasComponent<Castle>())
                    castleCollisionCheck(world, dt, player, collider);

                if (collider->hasComponent<Princess>())
                    princessCollisionCheck(world, dt, player);
            }
        }
    }
};