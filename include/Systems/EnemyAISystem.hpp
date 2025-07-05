#pragma once
#include <World.hpp>
#include <Components/Input.hpp>
#include <Components/RigidBody.hpp>
#include <Core/Variables.hpp>

class EnemyAISystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<EnemyTag>())
        {
            if (!input.moveLeft && !input.moveRight)
            {
                input.moveRight = true;
            }
            else
            {
                
            }
        }
    }
};