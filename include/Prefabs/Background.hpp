#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Background/Components.hpp>

class Background : public Entity
{
public:
    Background(float x, float y, float width, float height, int scale, int index)
    {
        // Add background tag
        // addComponent<BlockTag>();

        // Set the size of the collision box for the background
        // addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        // Set the transform for the background
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        if (index == 0)
        {
            // Add the castle tag
            addComponent<Castle>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Castle.png"));
        }
        else if (index == 1)
        {
            // Add the small hill tag
            addComponent<SmallHill>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/SmallHill.png"));
        }
        else if (index == 2)
        {
            // Add the big hill tag
            addComponent<BigHill>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/BigHill.png"));
        }
        else if (index == 3)
        {
            // Add the cloud1 tag
            addComponent<Cloud2>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Cloud2.png"));
        }
        else if (index == 4)
        {
            // Add the cloud2 tag
            addComponent<Cloud3>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Cloud3.png"));
        }
        else if (index == 5)
        {
            // Add the cloud3 tag
            addComponent<Cloud1>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Cloud1.png"));
        }
        else if (index == 6)
        {
            // Add the plant1 tag
            addComponent<Plant1>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Plant1.png"));
        }
        else if (index == 7)
        {
            // Add the plant2 tag
            addComponent<Plant3>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Plant3.png"));
        }
        else if (index == 8)
        {
            // Add the plant3 tag
            addComponent<Plant2>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Plant2.png"));
        }
        else if (index == 9)
        {
            // Add the flagpole tag
            addComponent<FlagPole>();

            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/FlagPole.png"));
        }
    }
};