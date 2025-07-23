#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <vector>
class Coin1 : public Entity
{
public:
    Coin1(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the animation for the coin
        std::vector<const sf::Texture *> textures = {
            &TextureManager::load("assets/Item/Coin/Coin1_0.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_1.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_2.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_3.png")};
        addComponent<Animation>(textures, width, height, 0.15, true);

        // addComponent<CollectableTag>();

        addComponent<LifeSpan>(0.5f);

        addComponent<Coin1Tag>();

        // addComponent<RigidBody>(sf::Vector2f(0, -600));
        // addComponent<Transform>(sf::Vector2f(x, y), SIZE::GRID);
    }
};

class Coin2 : public Entity
{
};