#pragma once

#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Obstacles/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

#include <iostream>
#include <stdlib.h>

class FireBar : public Entity
{
public:
    FireBar(float x, float y, float scale, int index, ItemFactory itemFactory)
    {
        float width = 0;
        float height = 0;

        if (index == 1)
        {
            addComponent<Animation>(itemFactory.getItemTexture("smallFireBar"));
            width = 24;
            height = 144;
        }
        else if (index == 2)
        {
            addComponent<Animation>(itemFactory.getItemTexture("largeFireBar"));
            width = 24;
            height = 288;
        }

        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height));

        // Set the collision box for the FireBar
        addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom, Direction::Top};
        addComponent<DamageOnContactComponent>(directions);

        bool direction = std::rand() % 2; // clockwise or counter-clockwise
        addComponent<FireBarComponent>(direction);
    }
};
