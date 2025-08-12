#pragma once
#include <Framework/World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Piranha/Components.hpp>
#include <iostream>

class EnemyScoreSystem : public System
{
private:
    void GoombaScore(World &world, float dt, Entity *enemy)
    {
        auto &pos = enemy->getComponent<Transform>().position;
        auto &size = enemy->getComponent<Transform>().size;

        Entity *player = world.findFirst<PlayerTag, ScoreComponent>();
        if (!player)
        {
            return;
        }
        auto &scoreComp = player->getComponent<ScoreComponent>();

        // If it has life span component
        if (enemy->hasComponent<LifeSpan>() && enemy->getComponent<LifeSpan>().value <= dt && !enemy->hasComponent<ScoreAddedTag>())
        {
            Entity *scoreTextEntity = world.createEntity();
            scoreTextEntity->addComponent<TextComponent>("100", pos.x, pos.y, pos.y - 48, 15, 1);
            scoreComp.score += 100;
            enemy->addComponent<ScoreAddedTag>();
        }

        auto &rb = enemy->getComponent<RigidBody>();
        if (rb.velocity.y < 0 && !enemy->hasComponent<ScoreAddedTag>())
        {
            Entity *scoreTextEntity = world.createEntity();
            scoreTextEntity->addComponent<TextComponent>("100", pos.x, pos.y, pos.y - 48, 15, 1);
            scoreComp.score += 100;
            enemy->addComponent<ScoreAddedTag>();
        }
    }
    void KoopaScore(World &world, float dt, Entity *enemy)
    {
        auto &pos = enemy->getComponent<Transform>().position;
        auto &size = enemy->getComponent<Transform>().size;
        Entity *player = world.findFirst<PlayerTag, ScoreComponent>();
        if (!player)
        {
            return;
        }
        auto &scoreComp = player->getComponent<ScoreComponent>();

        // If it has life span component
        if (enemy->hasComponent<LifeSpan>() && enemy->getComponent<LifeSpan>().value <= dt)
        {
            Entity *scoreTextEntity = world.createEntity();
            scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y, pos.y - 48, 15, 1);
            scoreComp.score += 200;
        }

        auto &rb = enemy->getComponent<RigidBody>();
        if (rb.velocity.y < 0 && !enemy->hasComponent<ScoreAddedTag>())
        {
            Entity *scoreTextEntity = world.createEntity();
            scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y, pos.y - 48, 15, 1);
            scoreComp.score += 200;
            enemy->addComponent<ScoreAddedTag>();
        }

        if (!enemy->hasComponent<NotOnPatrolYet>() && enemy->hasComponent<KoopaPatrol>() && !enemy->hasComponent<ScoreAddedTag>())
        {
            auto &koopa = enemy->getComponent<KoopaPatrol>();

            if (koopa.velocity.x == 0)
            {
                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>("100", pos.x, pos.y, pos.y - 48, 15, 1);
                scoreComp.score += 100;
                enemy->addComponent<ScoreAddedTag>();
            }
            else if (std::abs(koopa.velocity.x) == 1000)
            {
                Entity *scoreTextEntity = world.createEntity();
                scoreTextEntity->addComponent<TextComponent>("500", pos.x, pos.y, pos.y - 48, 15, 1);
                scoreComp.score += 500; // Increment score by 500 for Koopa
                enemy->addComponent<ScoreAddedTag>();
            }
        }
    }

    void PiranhaScore(World &world, float dt, Entity *enemy)
    {
        auto &pos = enemy->getComponent<Transform>().position;
        auto &size = enemy->getComponent<Transform>().size;
        Entity *player = world.findFirst<PlayerTag, ScoreComponent>();
        if (!player)
        {
            return;
        }
        auto &scoreComp = player->getComponent<ScoreComponent>();
        if (enemy->hasComponent<DespawnTag>())
        {
            Entity *scoreTextEntity = world.createEntity();
            scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y, pos.y - 48, 15, 1);
            scoreComp.score += 200; // Increment score by 500 for Koopa
        }
    }

public:
    void update(World &world, float dt) override
    {
        for (Entity *enemy : world.findAll<EnemyTag, Transform, RigidBody>())
        {
            if (enemy->hasComponent<GoombaPatrol>())
            {
                GoombaScore(world, dt, enemy);
            }
            else if (enemy->hasComponent<KoopaPatrol>())
            {
                KoopaScore(world, dt, enemy);
            }
            else if (enemy->hasComponent<PiranhaPatrol>())
            {
                PiranhaScore(world, dt, enemy);
            }
        }
    }
};