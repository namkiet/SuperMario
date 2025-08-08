#pragma once
#include <World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/Variables.hpp>

class MovementSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<Transform, RigidBody>())
        {
            auto& rb = entity->getComponent<RigidBody>();
            auto& tf = entity->getComponent<Transform>();

            tf.prevPos = tf.position;

            tf.position.x += rb.velocity.x * dt;
            tf.position.y += std::min(rb.velocity.y * dt, 100.0f);
            
            if (tf.position.y >= SIZE::SCREEN.y)
            {
                entity->addComponent<DespawnTag>();
            }
        }
    }
};