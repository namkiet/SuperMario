#pragma once
#include <World.hpp>
#include <Gameplay/Enemy/Components.hpp>

class EnemyBehaviourSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<EnemyTag>())
        {
            auto& tag = entity->getComponent<EnemyTag>();
            tag.behaviour->collideWithPlayer(entity);
            tag.behaviour->collideWithOther(entity);
            tag.behaviour->patrol(entity, dt, world);
            tag.behaviour->attack(entity, dt, world);
        }
    }
};