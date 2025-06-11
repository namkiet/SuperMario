#pragma once
#include <World.hpp>
#include <Components/Input.hpp>
#include <Components/RigidBody.hpp>

class PlayerControlSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Input, RigidBody>())
        {
            auto& input = entity->getComponent<Input>();
            auto& rb = entity->getComponent<RigidBody>();

            auto vel = rb.getVelocity();

            if (input.moveLeft)
            {
                vel.x = -100.f;
            } 
            else if (input.moveRight)
            {
                vel.x = 100.f;
            }
            else
            {
                vel.x = 0.f;
            }

            if (input.jumpPressed)
            {
                vel.y = -100.f;
            }

            rb.setVelocity(vel);
        }
    }
};