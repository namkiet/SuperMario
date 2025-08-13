#pragma once
#include <World.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Prefabs/Fireworks.hpp>
#include <Prefabs/Background.hpp>

#include <Factories/ItemFactory.hpp>
#include <iostream>

class LevelCompletionSystem : public System
{
private:
    void castleCollisionCheck(World &world, float dt, Entity *player, Entity *collider)
    {
        Entity *gameSession = world.findFirst<TimeComponent>();
        if (!gameSession)
            return;

        auto &castlePos = collider->getComponent<Transform>().position;
        auto &castleSize = collider->getComponent<Transform>().size;

        auto &timeComponent = gameSession->getComponent<TimeComponent>();

        // Check if the player has reached the flagpole

        if (player->hasComponent<Animation>())
            player->removeComponent<Animation>();
        player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);

        // Create castle flag if timer runs out
        if (timeComponent.timer <= 0 && !timeComponent.firstTimeReach0)
        {
            float x = (castlePos.x + 48 * 2) / 3;
            float y = (castlePos.y) / 3;
            auto castleFlag = world.createEntity<Background>(x, y, 14, 14, 3, 11);
            ItemEmerging emerging;
            emerging.finalY = castlePos.y - 14 * 3;
            castleFlag->addComponent<ItemEmerging>(emerging);
            timeComponent.firstTimeReach0 = true;
            // std::cout << "Castle flag is trigger to create" << std::endl;
        }

        Entity *flag = world.findFirst<CastleFlag>();

        // Create fireworks if the flag is present
        if (flag)
        {
            if (!player->hasComponent<FireworkComponent>())
            {
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
                    Entity *gameSession = world.findFirst<ThemeComponent>();
                    if (!gameSession)
                        return;
                    auto &themeComponent = gameSession->getComponent<ThemeComponent>();
                    world.createEntity<Fireworks>(48, 48, ItemFactory(themeComponent.currentTheme));

                    // Update score
                    world.getScoreManager().addScore(100);

                    // Decrease the fireworks left count
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
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D, RigidBody>())
        {
            for (const auto &[collider, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<Transform>())
                    continue;

                if (collider->hasComponent<Castle>())
                    castleCollisionCheck(world, dt, player, collider);

                if (collider->hasComponent<Princess>())
                    princessCollisionCheck(world, dt, player);

                if (collider->hasComponent<Castle>() || collider->hasComponent<Princess>())
                {
                    Entity *gameSession = world.findFirst<TimeComponent>();
                    if (!gameSession)
                        return;

                    auto &timeComponent = gameSession->getComponent<TimeComponent>();
                    timeComponent.goesFaster = true;

                    // Update score
                    if (timeComponent.timer > 0)
                    {
                        world.getScoreManager().addScore(50);
                    }
                }
            }
        }
    }
};