#pragma once
#include <ECS/Component.hpp>
#include <World.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/EnemyState.hpp>

class EnemyStateSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<EnemyTag>())
        {
            auto& tag = entity->getComponent<EnemyTag>();
            auto newState = tag.state->getNewState(entity, dt);

            if (newState)
            {
                tag.state = newState;
                tag.state->onEnter(entity);
            }
        }
    }
};