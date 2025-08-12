#pragma once
#include <Framework/World.hpp>

#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Gameplay/Obstacles/Components.hpp>

#include <Core/TextureManager.hpp>

#include <iostream>

class FireBarSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *fireBar : world.findAll<FireBarComponent, Transform, BoxCollider2D>())
        {
            auto &fireBarComp = fireBar->getComponent<FireBarComponent>();
            auto &tf = fireBar->getComponent<Transform>();
            auto &box = fireBar->getComponent<BoxCollider2D>();           

            // Update the angle of the fire bar
            if (fireBarComp.isClockwise)
            {
                fireBarComp.angle += dt * 100.0f; // Rotate at 50 degrees per second
            }
            else
            {
                fireBarComp.angle -= dt * 100.0f; // Rotate at 50 degrees per second
            }

            // Ensure the angle stays within 0-360 degrees
            if (fireBarComp.angle >= 360.0f)
            {
                fireBarComp.angle -= 360.0f;
            }

            box.rotation = fireBarComp.angle;
        }
    }
};