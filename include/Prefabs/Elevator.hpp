#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/Background/Components.hpp>
#include <iostream>

class Elevator : public Entity
{
public:
    // Direction: 1: up, 2: down, 3: left, 4:right
    Elevator(float x, float y, int scale, int index, int direction)
    {
        float width = 0;
        float height = 0;
        if (index == 1)
        {
            addComponent<Animation>(TextureManager::load("assets/Item/Elevator/Elevator1.png"));
            width = 24;
            height = 7;
        }
        else if (index == 2)
        {
            addComponent<Animation>(TextureManager::load("assets/Item/Elevator/Elevator2.png"));
            width = 32;
            height = 7;
            // std::cout << "Elevator2 created at (" << x << ", " << y << ")" << std::endl;
        }
        else if (index == 3)
        {
            addComponent<Animation>(TextureManager::load("assets/Item/Elevator/Elevator3.png"));
            width = 48;
            height = 7;
        }

        // Set the size of the collision box for the elevator
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        // Set the transform for the elevator
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        addComponent<ElevatorComponent>(x * scale, (x + width * 2) * scale, direction);
    }
};