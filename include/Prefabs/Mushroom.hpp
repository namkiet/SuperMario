#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Core/TextureManager.hpp>
#include <vector>

class Mushroom1 : public Entity
{
public:
    Mushroom1(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        // addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        addComponent<Animation>(TextureManager::load("assets/Item/Mushroom/Mushroom1_0.png"));

        // addComponent<CollectableTag>();
    }
};

class Mushroom2 : public Entity
{
    public:
    Mushroom2(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        // addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        addComponent<Animation>(TextureManager::load("assets/Item/Mushroom/Mushroom1_1.png"));

        // addComponent<CollectableTag>();
    }
};