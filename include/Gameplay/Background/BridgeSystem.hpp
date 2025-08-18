#pragma once
#include <Framework/World.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

#include <TimeManager.hpp>

#include <iostream>

class BridgeSystem : public System
{
private:
    void firstHitCheck(World &world, Entity *player, Entity *collider)
    {
        Entity *fakeBowser = world.findFirst<BowserPatrol>();
        if (!fakeBowser)
        {
            return;
        }
        // Get all bridge tiles
        auto bridgeTiles = world.findAll<BridgeTileTag, Transform>();

        std::vector<Entity *> sortedTiles(bridgeTiles.begin(), bridgeTiles.end());
        std::sort(sortedTiles.begin(), sortedTiles.end(), [](Entity *a, Entity *b)
                  { return a->getComponent<Transform>().position.x > b->getComponent<Transform>().position.x; });

        float delay = 0.0f;
        float step = 0.1f;

        for (Entity *tile : sortedTiles)
        {
            tile->addComponent<LifeSpan>(delay);
            delay += step;
        }

        collider->getComponent<BellTag>().firstHit = true;
    }

    void normalBlockCheck(World &world, Entity *player)
    {
        // Check if the fakebowser is still alive or not
        // If not, trigger the normal block to turn into debris
        Entity *fakeBowser = world.findFirst<BowserPatrol>();
        Entity *bell = world.findFirst<BellTag>();

        // Only go remove normal block if there is no fake bowser but still has bell
        if (fakeBowser)
            return;
        if (!bell)
            return;
        // Check if there is any debris existed in the entites vector
        Entity *debris = world.findFirst<DebrisTag>();
        if (debris)
            return;

        // If there is no debris, we can turn the normal block into debris
        Entity *normalBlock = world.findFirst<NormalBlock, Transform>();
        if (!normalBlock)
            return;
        normalBlock->addComponent<DespawnTag>();

        // Turn the normal block into debris
        auto &pos = normalBlock->getComponent<Transform>().position;
        world.createEntity<SmallDebris1>(pos.x, pos.y, 24.0f, 24.0f);
        world.createEntity<SmallDebris2>(pos.x, pos.y, 24.0f, 24.0f);
        world.createEntity<SmallDebris3>(pos.x, pos.y, 24.0f, 24.0f);
        world.createEntity<SmallDebris4>(pos.x, pos.y, 24.0f, 24.0f);
    }

    void secondHitCheck(World &world, Entity *player, Entity *collider)
    {
        Entity *normalBlock = world.findFirst<NormalBlock, Transform>();
        if (normalBlock)
            return;

        player->addComponent<RigidBody>(sf::Vector2f(200, 0));
        if (player->hasComponent<InputTag>())
            player->removeComponent<InputTag>();

        collider->getComponent<BellTag>().secondHit = true;
        TimeManager::instance().setTimePaused(true);
    }

public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D, RigidBody, Transform>())
        {
            auto &pos = player->getComponent<Transform>().position;
            auto &size = player->getComponent<BoxCollider2D>().size;

            for (const auto &[collider, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (collider->hasComponent<BellTag>() && collider->hasComponent<Transform>() && collider->hasComponent<BoxCollider2D>())
                {
                    auto &bellTag = collider->getComponent<BellTag>();
                    if (direction == Direction::Top && !bellTag.firstHit)
                        firstHitCheck(world, player, collider);
                    if (direction != Direction::Left && !bellTag.secondHit)
                        secondHitCheck(world, player, collider);
                    auto &blockPos = collider->getComponent<Transform>().position;
                    auto &blockSize = collider->getComponent<BoxCollider2D>().size;
                    if (pos.y + size.y <= blockPos.y + blockSize.y)
                        secondHitCheck(world, player, collider);
                }
                normalBlockCheck(world, player);
            }
        }
    }
};