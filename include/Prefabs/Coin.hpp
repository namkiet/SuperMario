#pragma once
#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/PassThroughTag.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <vector>

class Coin1 : public Entity
{
public:
    Coin1(float x, float y, float width, float height, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // // Set the animation for the coin
        std::vector<const sf::Texture *> textures = itemFactory.getItemTextures("coin1");
        addComponent<Animation>(textures, width, height, 0.15f, true);

        // addComponent<Animation>(TextureManager::load("assets/Item/Coin/coin.png"), 16, 16, 16, 0.15);

        // addComponent<CollectableTag>();

        addComponent<LifeSpan>(0.5f);

        addComponent<Coin1Tag>();

        // addComponent<RigidBody>(sf::Vector2f(0, -600));
        // addComponent<Transform>(sf::Vector2f(x, y), SIZE::GRID);
    }
};

class SmallCoin : public Entity
{
public:
    SmallCoin(float x, float y, float width, float height, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the animation for the coin
        std::vector<const sf::Texture *> textures = itemFactory.getItemTextures("coin3");
        addComponent<Animation>(textures, width, height, 0.3f, true);

        addComponent<PassThroughTag>();
        addComponent<SmallCoinTag>();
    }
};

class Coin2 : public Entity
{
public:
    Coin2(float x, float y, float width, float height, float scale, ItemFactory itemFactory)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the animation for the coin
        std::vector<const sf::Texture *> textures = itemFactory.getItemTextures("coin2");
        addComponent<Animation>(textures, width, height, 0.3f, true);

        // addComponent<Animation>(TextureManager::load("assets/Item/Coin/coin.png"), 16, 16, 16, 0.15);

        addComponent<CollectableTag>();

        // addComponent<LifeSpan>(0.5f);

        addComponent<Coin2Tag>();

        // addComponent<RigidBody>(sf::Vector2f(0, -600));
    }
};