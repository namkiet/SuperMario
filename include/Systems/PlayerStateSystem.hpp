#pragma once
#include <ECS/Component.hpp>
#include <Components/PlayerTag.hpp>
#include <iostream>

class PlayerStateSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<PlayerTag>())
        {
            auto& tag = entity->getComponent<PlayerTag>();
            auto newState = tag.state->getNewState(entity);

            if (newState)
            {
                // tag.state->onExit(entity);
                tag.state = newState;
                tag.state->onEnter(entity);
            }
        }
    }
};