#pragma once
#include <World.hpp>
#include <Components/Transform.hpp>
#include <Components/RigidBody.hpp>

class MovementSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Transform, RigidBody>())
        {
            auto& tf = entity->getComponent<Transform>();
            auto& rb = entity->getComponent<RigidBody>();

            auto pos = tf.getPosition();
            auto vel = rb.getVelocity();
            
            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            tf.setPosition(pos);
        }
    }
};
