#pragma once
#include <World.hpp>

#include <Core/Variables.hpp>

#include <Gameplay/Background/Components.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <iostream>

class ElevatorCollisionSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D, Transform, RigidBody>())
        {
            auto &box = player->getComponent<BoxCollider2D>();
            auto &tf = player->getComponent<Transform>();
            auto &rb = player->getComponent<RigidBody>();

            for (const auto &[elevator, direction, overlap] : box.collisions)
            {
                if (!elevator->hasComponent<ElevatorComponent>())
                    continue;
                if (!elevator->hasComponent<BoxCollider2D>())
                    continue;
                if (!elevator->hasComponent<Transform>())
                    continue;

                auto &elevatorComp = elevator->getComponent<ElevatorComponent>();
                auto &elevatorPos = elevator->getComponent<Transform>().position;
                auto &elevatorSize = elevator->getComponent<BoxCollider2D>().size;

                // Handle collision based on direction
                switch (direction)
                {
                case Direction::Top:
                    tf.position.y = elevatorPos.y - box.size.y;
                    rb.velocity.y = 0.0f;
                    rb.onGround = true;
                    if (elevatorComp.direction == ElevatorComponent::Direction::Left)
                        tf.position.x -= 100 * dt; // Move left with the elevator
                    else if (elevatorComp.direction == ElevatorComponent::Direction::Right)
                        tf.position.x += 100 * dt; // Move right with the elevator
                    break;
                case Direction::Bottom:
                    tf.position.y = elevatorPos.y - box.size.y;
                    rb.velocity.y = 0.0f;
                    rb.onGround = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
};