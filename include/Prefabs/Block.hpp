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
    Block(float x, float y, float width, float height, int scale, int index, int currentLevel = 1)
    {
        // Add the block tag
        addComponent<BlockTag>();

        // Set the size of the collision box for the block
        addComponent<BoxCollider2D>(sf::Vector2f(width * scale, height * scale));

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x * scale, y * scale), sf::Vector2f(width * scale, height * scale));

        // Add different types for different block types
        if (index < 0)
        {
            // Add the ground block tag
            addComponent<GroundBlock>();
            return;
        }

        std::string tileFolder = "assets/Tile/Tile" + std::to_string(currentLevel) + "/";
        if (index >= 1 && index <= 4) // Question blocks with animation
        {
            addComponent<QuestionBlockTag>();
            switch (index)
            {
            case 1:
                addComponent<CoinQuestionBlock>();
                break;
            case 2:
                addComponent<MushroomQuestionBlock>();
                break;
            case 3:
                addComponent<FlowerQuestionBlock>();
                break;
            case 4:
                addComponent<StarQuestionBlock>();
                break;
            }

            std::vector<const sf::Texture *> textures = {
                &TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_24.png"),
                &TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_25.png"),
                &TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_26.png")};
            addComponent<Animation>(textures, width, height, 0.3f, true);
        }
        else if (index == 5) // Normal block
        {
            addComponent<NormalBlock>();
            addComponent<Animation>(TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_2.png"));
        }
        else if (index == 6) // Coin block
        {
            addComponent<CoinBlock>();
            addComponent<Animation>(TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_2.png"));
            addComponent<CoinBlockComponent>();
        }

        else if (index == 7) // Stairs block
        {
            addComponent<StairsBlock>();
            addComponent<Animation>(TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_28.png"));
        }
        else if (index == 8)
        {
            // Add the level up block tag
            addComponent<LevelUpBlock>();

            removeComponent<BlockTag>();
        }
        else if (index == 9)
        {
            // Add the star block tag
            addComponent<StarBlock>();

            // Get the texture for the block
            addComponent<Animation>(TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_2.png"));

            // std::cout << "star block added" << std::endl;
        }
        else if (index == 10) // Flag block
        {
            addComponent<FlagBlock>();
            addComponent<Animation>(TextureManager::load(tileFolder + "Tile" + std::to_string(currentLevel) + "_28.png"));
        }
    }
};