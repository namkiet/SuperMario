#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <iostream>

class InvincibleSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity* entity : world.findAll<InvincibleTag, PlayerTag>())
        {
            auto& timer = entity->getComponent<InvincibleTag>().timer;
            const auto& duration = entity->getComponent<InvincibleTag>().duration;

            // std::cout << "Timer: " << timer << ", duration: " << duration << "\n";

            if (timer == 0.0f)
            {
                entity->addComponent<CanKillEnemyTag>();
                entity->removeComponent<CanGetDamageTag>();
            }
            else if (timer >= duration)
            {
                entity->removeComponent<CanKillEnemyTag>();
                entity->addComponent<CanGetDamageTag>();
                entity->removeComponent<InvincibleTag>();
                continue;
            }

            timer += dt;
        }
    }
};