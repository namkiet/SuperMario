#pragma once
#include <World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/Variables.hpp>

class MovementSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Transform, RigidBody>())
        {
            auto& vel = entity->getComponent<RigidBody>().velocity;
            auto& tf = entity->getComponent<Transform>();
            auto& pos = tf.position;
            auto& prev = tf.prevPos;

            prev.x = pos.x;
            prev.y = pos.y;
            
            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            if (pos.y >= SIZE::SCREEN.y)
            {
                entity->addComponent<DespawnTag>();
            }

            if (vel.x > 0.0f)
            {
                tf.isFacingRight = true;
            }
            else if (vel.x < 0.0f)
            {
                tf.isFacingRight = false;
            }
        }
    }
};
