#pragma once
#include <World.hpp>
#include <Components/Gravity.hpp>
#include <Components/RigidBody.hpp>

class GravitySystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Gravity, RigidBody>())
        {
            auto& gra = entity->getComponent<Gravity>();
            auto& rb = entity->getComponent<RigidBody>(); 
            
            auto vel = rb.getVelocity();
            vel.y += gra.g * dt;

            rb.setVelocity(vel);
        }
    }
};