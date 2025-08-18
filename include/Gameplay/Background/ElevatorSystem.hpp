#pragma once
#include <ECS/System.hpp> 
#include <Framework/World.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Gameplay/Background/Components.hpp>
#include <iostream>

class ElevatorSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *elevator : world.findAll<ElevatorComponent, BoxCollider2D, Transform>())
        {
            handleOutOfRange(elevator);
            carryEntites(elevator, dt);   
        }
    }

private:
    void handleOutOfRange(Entity* elevator)
    {
        const auto& elevatorComp = elevator->getComponent<ElevatorComponent>();
        auto& pos = elevator->getComponent<Transform>().position;
        auto& size = elevator->getComponent<Transform>().size;

        // Out of verical range
        if (pos.y <= elevatorComp.minY)
        {
            pos.y = elevatorComp.maxY;
        }
        else if (pos.y >= elevatorComp.maxY)
        {
            pos.y = elevatorComp.minY;
        }

        // Out of horizontal range
        if (pos.x <= elevatorComp.minX) 
        {
            pos.x = elevatorComp.minX;
            if (elevator->hasComponent<RigidBody>())
            {
                auto& vel = elevator->getComponent<RigidBody>().velocity;
                vel.x = std::abs(vel.x);
            }
        }
        else if (pos.x >= elevatorComp.maxX) 
        {
            pos.x = elevatorComp.maxX;
            if (elevator->hasComponent<RigidBody>())
            {
                auto& vel = elevator->getComponent<RigidBody>().velocity;
                vel.x = -std::abs(vel.x);
            }
        }
    }

    void carryEntites(Entity* elevator, float dt)
    {
        if (!elevator->getComponent<ElevatorComponent>().isHorizontal) return;

        for (auto& [other, direction, _] : elevator->getComponent<BoxCollider2D>().collisions)
        {
            if (direction != Direction::Bottom) continue;
            if (!other->hasComponent<Transform>()) continue;
            other->getComponent<Transform>().position.x += elevator->getComponent<RigidBody>().velocity.x * dt;
        }
    }
};