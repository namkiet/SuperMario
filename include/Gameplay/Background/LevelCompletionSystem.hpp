#pragma once

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <LevelManager.hpp>

#include <Prefabs/Fireworks.hpp>
#include <Prefabs/Background.hpp>

#include <ScoreManager.hpp>

#include <TimeManager.hpp>

#include <World.hpp>

class LevelCompletionSystem : public System
{
private:
    float timeElapsed = 0.0f;
    void castleCollisionCheck(World &world, float dt, Entity *player, Entity *collider)
    {
        auto &castlePos = collider->getComponent<Transform>().position;
        auto &castleSize = collider->getComponent<Transform>().size;

        if (player->hasComponent<Animation>())
            player->removeComponent<Animation>();

        player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);

        // Create castle flag if timer runs out
        if (TimeManager::instance().getTime() <= 0 && !TimeManager::instance().getFirstTimeReach0())
        {
            float x = (castlePos.x + 48 * 2) / 3;
            float y = (castlePos.y) / 3;
            auto castleFlag = world.createEntity<Background>(x, y, 14.0f, 14.0f, 3.0f, 11);

            ItemEmerging emerging;
            emerging.finalY = castlePos.y - 14 * 3;

            castleFlag->addComponent<ItemEmerging>(emerging);

            TimeManager::instance().setFirstTimeReach0(true);
        }

        Entity *flag = world.findFirst<CastleFlag>();

        // Create fireworks if the flag is present
        if (flag)
        {
            if (!player->hasComponent<FireworkComponent>())
            {
                int n = TimeManager::instance().getTimeUnitLeft();
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
                    world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/fire.wav"));
                    world.createEntity<Fireworks>(48.0f, 48.0f);

                    // Update score
                    ScoreManager::instance().addScore(100);

                    // Decrease the fireworks left count
                    --seq.fireworksLeft;
                }
            }

            if (player->hasComponent<FireworkComponent>())
            {
                timeElapsed += dt;
                auto &seq = player->getComponent<FireworkComponent>();
                if (seq.fireworksLeft <= 0 && timeElapsed > 3.0f)
                {
                    LevelManager::instance().setStatus("win");
                }
            }
            else
            {
                timeElapsed += dt;
                if (timeElapsed > 3.0f)
                {
                    LevelManager::instance().setStatus("win");
                }
            }
        }
    }
    void princessCollisionCheck(World &world, float dt, Entity *player)
    {
        player->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);

        if (TimeManager::instance().getTime() <= 0)
        {
            timeElapsed += dt;
        }

        if (timeElapsed > 3.0f)
        {
            LevelManager::instance().setStatus("win");
        }
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
                    TimeManager::instance().setTimeGoesFaster(true);

                    // Update score
                    if (TimeManager::instance().getTime() > 0)
                    {
                        ScoreManager::instance().addScore(50);
                        world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/coin.wav"));
                    }
                }
            }
        }
    }
};