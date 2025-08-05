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
#include <Engine/Physics/PassThroughTag.hpp>
#include <vector>

class Coin1 : public Entity
{
public:
    Coin1(float x, float y, float width, float height)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // // Set the animation for the coin
        std::vector<const sf::Texture *> textures = {
            &TextureManager::load("assets/Item/Coin/Coin1_0.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_1.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_2.png"),
            &TextureManager::load("assets/Item/Coin/Coin1_3.png")};
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
    SmallCoin(float x, float y, float width, float height, int currentLevel)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(width, height));

        // Set the animation for the coin
        std::string tileFolder = "assets/Item/Coin/";
        std::vector<const sf::Texture *> textures = {
            &TextureManager::load(tileFolder + "SmallCoin" + std::to_string(currentLevel) + "_0.png"),
            &TextureManager::load(tileFolder + "SmallCoin" + std::to_string(currentLevel) + "_1.png"),
            &TextureManager::load(tileFolder + "SmallCoin" + std::to_string(currentLevel) + "_2.png"),};
        addComponent<Animation>(textures, width, height, 0.3f, true);

        addComponent<PassThroughTag>();
        addComponent<SmallCoinTag>();
    }
};

class Coin2 : public Entity
{
public:
    Coin2(float x, float y, float width, float height, float scale, int currentLevel)
    {
        // Set the transform for positioning
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        std::string tileFolder = "assets/Item/Coin/";

        //
        std::vector<const sf::Texture *> textures = {
            &TextureManager::load(tileFolder + "Coin" + std::to_string(currentLevel) + "_4.png"),
            &TextureManager::load(tileFolder + "Coin" + std::to_string(currentLevel) + "_5.png"),
            &TextureManager::load(tileFolder + "Coin" + std::to_string(currentLevel) + "_6.png"),
            &TextureManager::load(tileFolder + "Coin" + std::to_string(currentLevel) + "_7.png")};
        addComponent<Animation>(textures, width, height, 0.3f, true);

        // addComponent<Animation>(TextureManager::load("assets/Item/Coin/coin.png"), 16, 16, 16, 0.15);

        addComponent<CollectableTag>();

        // addComponent<LifeSpan>(0.5f);

        addComponent<Coin2Tag>();

        // addComponent<RigidBody>(sf::Vector2f(0, -600));
    }
};