#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Rendering/ZIndex.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Background/Components.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <iostream>

class Background : public Entity
{
public:
    Background(float x, float y, float width, float height, float scale, int index)
    {
        // Set the size of the collision box for the background
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the transform for the background
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        if (index == 0)
        {
            // Add the castle tag
            addComponent<Castle>();

            getComponent<BoxCollider2D>().offset = sf::Vector2f(144.0f, (float)(48 * 3));
            getComponent<BoxCollider2D>().size = sf::Vector2f(48.0f, 96.0f);
            // Set the texture for the background
            addComponent<Animation>(TextureManager::load("assets/Background/Castle.png"));
            addComponent<ZIndex>(-2);
        }

        else if (index == 9)
        {
            // Add the flagpole tag
            addComponent<FlagPoleTag>();

            // addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

            // Set the texture for the background
            // addComponent<Animation>(TextureManager::load("assets/Background/FlagPole.png"));
        }
        else if (index == 10)
        {
            addComponent<Flag>();

            addComponent<CanHitBlockTag>();

            addComponent<Animation>(TextureManager::load("assets/Background/Flag.png"));
            addComponent<ZIndex>(-3);
        }
        else if (index == 11)
        {
            addComponent<CastleFlag>();

            addComponent<Animation>(TextureManager::load("assets/Background/CastleFlag.png"));

            // std::cout << "Castle flag created at position: " << x * scale << ", " << y * scale << std::endl;
        }
        else if (index == 12)
        {
            addComponent<Princess>();
        }
    }
};