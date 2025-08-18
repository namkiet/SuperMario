#pragma once
#include <Framework/World.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
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
            if (rb.applyGravity) // now, applyGravity is always true
            {
                rb.velocity.y += PHYSICS::GRAVITY * dt;
                rb.velocity.y += rb.antiGravity * dt;
            }
        }
    }
};