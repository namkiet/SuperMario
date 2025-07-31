#pragma once
#include <World.hpp>
#include <Prefabs/Coin.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Score/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <iostream>

class EnemyScoreSystem : public System
{
private:
public:
    void update(World &world, float dt) override
    {
        for (Entity *enemy : world.findAll<EnemyTag, Transform, LifeSpan>())
        {
            auto &pos = enemy->getComponent<Transform>().position;
            auto &size = enemy->getComponent<Transform>().size;
            auto &lifeSpan = enemy->getComponent<LifeSpan>();

            if (lifeSpan.value <= dt)
            {
                Entity *scoreTextEntity = world.createEntity();
                if (enemy->hasComponent<GoombaPatrol>())
                    scoreTextEntity->addComponent<TextComponent>("100", pos.x, pos.y, pos.y - 48, 15, 1);
                else if (enemy->hasComponent<KoopaPatrol>())
                    scoreTextEntity->addComponent<TextComponent>("200", pos.x, pos.y, pos.y - 48, 15, 1);

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
                    if (enemy->hasComponent<GoombaPatrol>())
                        scoreComp.score += 100; // Increment score by 100 for Goomba
                    else if (enemy->hasComponent<KoopaPatrol>())
                        scoreComp.score += 200; // Increment score by 100
                }
            }
        }
    }
};