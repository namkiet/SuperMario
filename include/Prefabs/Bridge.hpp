#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/Background/Components.hpp>
#include <iostream>

class Bridge : public Entity
{
public:
    Bridge(float x, float y, int scale, int index)
    {
        float width = 0;
        float height = 0;
        if (index == 1)
        {
            width = 16;
            height = 12;

            // Set the texture for the bridge
            addComponent<Animation>(TextureManager::load("assets/Item/Bridge/Bridge1.png"));

            // Add block tag to the bridge
            addComponent<BlockTag>();
        }
        else if (index == 2)
        {
            width = 15;
            height = 14;

            // Set the texture for the bridge
            addComponent<Animation>(TextureManager::load("assets/Item/Bridge/Bridge2.png"));
        }
        // Set the size of the collision box for the bridge
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        // Set the transform for the bridge
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        addComponent<BridgeTileTag>();
    }
};