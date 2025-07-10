#pragma once
#include <World.hpp>
#include <Components/RigidBody.hpp>
#include <Components/Transform.hpp>
#include <Core/Variables.hpp>
#include <iostream>

class GravitySystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<RigidBody>())
        {
            auto& rb = entity->getComponent<RigidBody>();
            if (rb.applyGravity) 
            {
                rb.velocity.y += PHYSICS::GRAVITY * dt;
            }
        }
    }
};