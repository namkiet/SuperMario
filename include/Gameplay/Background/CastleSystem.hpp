#pragma once
#include <World.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Score/Components.hpp>
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

class CastleCollisionSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D>())
        {
            for (const auto &[collider, direction] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<Castle>())
                    continue;

                auto &castlePos = collider->getComponent<Transform>().position;
                auto &castleSize = collider->getComponent<Transform>().size;

                // Check if the player has reached the flagpole

                if (direction != Direction::None)
                {
                    // Make the player disappear
                    player->removeComponent<Animation>();
                }
                else
                    continue;

                if (player->hasComponent<TimeComponent>())
                {
                    auto &timeComponent = player->getComponent<TimeComponent>();
                    timeComponent.goesFaster = true;

                    if (timeComponent.timer <= 0 && !timeComponent.firstTimeReach0)
                    {
                        float x = (castlePos.x + 48 * 2) / 3;
                        float y = (castlePos.y) / 3;
                        auto castleFlag = world.createEntityAtFront<Background>(x, y, 14, 14, 3, 11);
                        ItemEmerging emerging;
                        emerging.finalY = castlePos.y - 14 * 3;
                        castleFlag->addComponent<ItemEmerging>(emerging);
                        timeComponent.firstTimeReach0 = true;
                        // std::cout << "Castle flag is trigger to create" << std::endl;
                    }
                }

                Entity *flag = nullptr;
                for (Entity *entity : world.findAll<CastleFlag>())
                {
                    if (entity->getComponent<Transform>().position.y == castlePos.y - 14 * 3)
                    {
                        flag = entity;

                        // Remove unnecessary components
                        entity->removeComponent<BoxCollider2D>();
                        entity->removeComponent<PatrolComponent>();
                        entity->removeComponent<RigidBody>();
                        entity->removeComponent<CollectableTag>();
                        entity->removeComponent<CanHitBlockTag>();
                        break;
                    }
                }

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
                    auto &seq = player->getComponent<FireworkComponent>();
                    if (seq.fireworksLeft > 0 && Fireworks::getFireworksCount() < 1)
                    {
                        world.createEntity<Fireworks>(48, 48);
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
    }
};