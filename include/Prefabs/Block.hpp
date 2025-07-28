#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Block/Components.hpp>
#include <vector>
#include <iostream>
class Block : public Entity
{
public:
    Block(float x, float y, float width, float height, int scale, int index)
    {
        // Add the block tag
        addComponent<BlockTag>();

        // Add different types for different block types
        if (index < 0)
        {
            // Add the ground block tag
            addComponent<GroundBlock>();

            addComponent<BoxCollider2D>(sf::Vector2f(width, height));

            addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width, height));

            if (index == -1)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_0.png"));
            else if (index == -2)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_1.png"));
            else if (index == -3)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_2.png"));
            else if (index == -4)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_3.png"));
            else if (index == -5)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_5.png"));
            else if (index == -6)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_7.png"));
            else if (index == -7)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_6.png"));
            else if (index == -8)
                // Get the texture for the block
                addComponent<Animation>(TextureManager::load("assets/Tile/Ground/Map11/Map11_8.png"));

            return;
        }

        // Set the size of the collision box for the block
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        if (index == 1)
        {
            // Add the coin question block tag
            addComponent<CoinQuestionBlock>();

            // Add the question block tag
            addComponent<QuestionBlockTag>();

            // Get the texture for the block
            std::vector<const sf::Texture *> textures = {
                &TextureManager::load("assets/Tile/Tile1/Tile1_24.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_25.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_26.png")};

            addComponent<Animation>(textures, width, height, 0.15f, true);
        }
        else if (index == 2)
        {
            // Add the mushroom question block tag
            addComponent<MushroomQuestionBlock>();

            // Add the question block tag
            addComponent<QuestionBlockTag>();

            // Get the texture for the block
            std::vector<const sf::Texture *> textures = {
                &TextureManager::load("assets/Tile/Tile1/Tile1_24.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_25.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_26.png")};

            addComponent<Animation>(textures, width, height, 0.15f, true);
        }
        else if (index == 3)
        {
            // Add the flower question block tag
            addComponent<FlowerQuestionBlock>();

            // Add the question block tag
            addComponent<QuestionBlockTag>();

            // Get the texture for the block
            std::vector<const sf::Texture *> textures = {
                &TextureManager::load("assets/Tile/Tile1/Tile1_24.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_25.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_26.png")};

            addComponent<Animation>(textures, width, height, 0.15f, true);
        }
        else if (index == 4)
        {
            // Add the star question block tag
            addComponent<StarQuestionBlock>();

            // Add the question block tag
            addComponent<QuestionBlockTag>();

            // Get the texture for the block
            std::vector<const sf::Texture *> textures = {
                &TextureManager::load("assets/Tile/Tile1/Tile1_24.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_25.png"),
                &TextureManager::load("assets/Tile/Tile1/Tile1_26.png")};

            addComponent<Animation>(textures, width, height, 0.15f, true);
        }
        else if (index == 5)
        {
            // Add the normal block tag
            addComponent<NormalBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_2.png"));
        }
        else if (index == 6)
        {
            // Add the coin block tag
            addComponent<CoinBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_2.png"));

            addComponent<CoinBlockComponent>();
        }
        else if (index == 7)
        {
            // Add the stairs block tag
            addComponent<StairsBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_28.png"));
        }
        else if (index == 8)
        {
            // Add the level up block tag
            addComponent<LevelUpBlock>();

            // Get the texture for the block
            // addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_2.png"));
        }
        else if (index == 9)
        {
            // Add the star block tag
            addComponent<StarBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_2.png"));

            // std::cout << "star block added" << std::endl;
        }
        else if (index == 10)
        {
            // Add the flag block tag
            addComponent<FlagBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_28.png"));
        }
    }
};