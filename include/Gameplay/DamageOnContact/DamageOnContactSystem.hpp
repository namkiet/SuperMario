#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

class DamageOnContactSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<CanGetDamageTag, BoxCollider2D>())
        {
            for (const auto& [collider, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {   
                if (!collider->hasComponent<DamageOnContactComponent>()) continue;
                auto& dmg = collider->getComponent<DamageOnContactComponent>();
                
                bool validHit = false;
                for (const auto& validDir : dmg.validDirections)
                {
                    if (direction == validDir)
                    {
                        validHit = true;
                        break;
                    }
                }

                if (validHit)
                {
                    entity->addComponent<DespawnTag>();
                    //std::cout << "despawned in damageOnContace system" << std::endl;
                }
            }
        }
    }
};