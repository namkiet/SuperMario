#pragma once

#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Background/Components.hpp>

class Elevator : public Entity
{
public:
    // Direction: 1: up, 2: down, 3: left, 4:right
    Elevator(float x, float y, float scale, int index, int direction, ItemFactory itemFactory)
    {
        float width = 0;
        float height = 0;

        sf::Vector2f vel(0, 0);
        if (direction == 1)
            vel.y = -100.0f;
        else if (direction == 2)
            vel.y = 100.0f;
        else if (direction == 3)
            vel.x = -100.0f;
        else if (direction == 4)
            vel.x = 100.0f;
        addComponent<RigidBody>(vel, false);

        if (index == 1)
        {
            addComponent<Animation>(itemFactory.getItemTexture("elevator1"));
            width = 24.0f;
            height = 7.0f;
        }
        else if (index == 2)
        {
            addComponent<Animation>(itemFactory.getItemTexture("elevator2"));
            width = 32.0f;
            height = 7.0f;
        }
        else if (index == 3)
        {
            addComponent<Animation>(itemFactory.getItemTexture("elevator3"));
            width = 48.0f;
            height = 7.0f;
        }

        // Set the size of the collision box for the elevator
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the transform for the elevator
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        if (direction == 3 || direction == 4)
        {
            addComponent<ElevatorComponent>(x * scale, (x + width * 2) * scale, true);
        }
        else
        {
            addComponent<ElevatorComponent>(48.0f * 2, SIZE::SCREEN.y, false);
        }

        addComponent<BlockTag>();
    }
};