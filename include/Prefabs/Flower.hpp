#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Core/TextureManager.hpp>
#include <vector>
class Flower : public Entity
{
public:
    Flower(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the collision box for the flower
        addComponent<BoxCollider2D>(sf::Vector2f(width, height));

        // Set the animation for the flower
        std::vector<const sf::Texture*> textures = {
            &TextureManager::load("assets/Item/Flower/Flower1_0.png"),
            &TextureManager::load("assets/Item/Flower/Flower1_1.png"),
            &TextureManager::load("assets/Item/Flower/Flower1_2.png"),
            &TextureManager::load("assets/Item/Flower/Flower1_3.png")};
        
        addComponent<Animation>(textures, width, height, 0.15f, true);

        // addComponent<CollectableTag>();
    }
};