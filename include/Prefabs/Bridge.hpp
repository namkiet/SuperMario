#pragma once

#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Background/Components.hpp>

#include <iostream>

class Bridge : public Entity
{
public:
    Bridge(float x, float y, float scale, int index)
    {
        float width = 0;
        float height = 0;
        if (index == 1)
        {
            width = 16.0f;
            height = 12.0f;

            // Set the texture for the bridge
            addComponent<Animation>(ItemFactory::getItemTexture("bridge1"));

            // Add block tag to the bridge
            addComponent<BlockTag>();
        }
        else if (index == 2)
        {
            width = 15.0f;
            height = 14.0f;

            // Set the texture for the bridge
            addComponent<Animation>(ItemFactory::getItemTexture("bridge2"));
        }
        // Set the size of the collision box for the bridge
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the transform for the bridge
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        addComponent<BridgeTileTag>();
    }
};