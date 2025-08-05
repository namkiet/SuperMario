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

class ElevatorSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *elevator : world.findAll<ElevatorComponent, BoxCollider2D, Transform>())
        {
            auto &elevatorPos = elevator->getComponent<Transform>().position;
            auto &elevatorSize = elevator->getComponent<Transform>().size;
            auto &elevatorComp = elevator->getComponent<ElevatorComponent>();

            // Check if the elevator is moving up or down
            if (elevator->getComponent<ElevatorComponent>().direction == ElevatorComponent::Direction::Up)
            {
                if (elevatorPos.y <= 0)
                {
                    elevatorPos.y = SIZE::SCREEN.y;
                    continue;
                }

                // Set the animation back if it was removed
                if (!elevator->hasComponent<Animation>() && elevatorPos.y > 32 * 3)
                {
                    elevator->addComponent<Animation>(elevatorComp.animation);
                }

                if (elevatorPos.y < 32 * 3)
                {
                    // Store the old animation
                    if (elevator->hasComponent<Animation>())
                    {
                        elevatorComp.animation = elevator->getComponent<Animation>();
                        elevator->removeComponent<Animation>();
                    }
                }
                elevatorPos.y -= 100 * dt; // Move up
            }
            else if (elevator->getComponent<ElevatorComponent>().direction == ElevatorComponent::Direction::Down)
            {
                if (elevatorPos.y >= SIZE::SCREEN.y)
                {
                    elevatorPos.y = 0;
                    // Store the old animation
                    if (elevator->hasComponent<Animation>())
                    {
                        elevatorComp.animation = elevator->getComponent<Animation>();
                        elevator->removeComponent<Animation>();
                    }
                    continue;
                }
                // Set the animation back if it was removed
                if (!elevator->hasComponent<Animation>() && elevatorPos.y > 32 * 3)
                {
                    elevator->addComponent<Animation>(elevatorComp.animation);
                }
                elevatorPos.y += 100 * dt; // Move down
            }
            else if (elevator->getComponent<ElevatorComponent>().direction == ElevatorComponent::Direction::Left)
            {
                // Calculate the min X position based on the original X
                if (elevatorPos.x <= elevatorComp.minimumX)
                {
                    // Change direction to right
                    elevatorComp.direction = ElevatorComponent::Direction::Right;
                    continue;
                }
                elevatorPos.x -= 100 * dt; // Move left
            }
            else if (elevator->getComponent<ElevatorComponent>().direction == ElevatorComponent::Direction::Right)
            {
                // Calculate the max X position based on the original X
                if (elevatorPos.x >= elevatorComp.maximumX)
                {
                    // Change direction to left
                    elevatorComp.direction = ElevatorComponent::Direction::Left;
                    continue;
                }
                elevatorPos.x += 100 * dt; // Move right
            }
        }
    }
};