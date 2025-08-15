#pragma once

#include <ECS/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/BlockFactory.hpp>

#include <Gameplay/Block/Components.hpp>

#include <vector>

#include <iostream>

class Block : public Entity
{
public:
    Block(float x, float y, float width, float height, float scale, int index, BlockFactory blockFactory)
    {
        // Add the block tag
        addComponent<BlockTag>();

        // Set the size of the collision box for the block
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

        // Add different types for different block types
        if (index < 0)
        {
            // Add the ground block tag
            addComponent<GroundBlock>();
            return;
        }
        else if (index == 0)
        {
            addComponent<StairsBlock>();
            return;
        }

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

            std::vector<const sf::Texture *> textures = blockFactory.getQuestionBlockTextures();
            addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
        }
        else if (index == 5) // Normal block
        {
            addComponent<NormalBlock>();
            addComponent<Animation>(blockFactory.getBlockTexture(2));
        }
        else if (index == 6) // Coin block
        {
            addComponent<CoinBlock>();
            addComponent<Animation>(blockFactory.getBlockTexture(2));
            addComponent<CoinBlockComponent>();
        }

        else if (index == 7) // Stairs block
        {
            addComponent<StairsBlock>();
            addComponent<Animation>(blockFactory.getBlockTexture(28));
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
            addComponent<Animation>(blockFactory.getBlockTexture(2));

            // std::cout << "star block added" << std::endl;
        }
        else if (index == 10) // Flag block
        {
            addComponent<FlagBlock>();
            addComponent<Animation>(blockFactory.getBlockTexture(28));
        }
        else if (index == 11)
        {
            addComponent<MushroomBlock>();
            addComponent<Animation>(blockFactory.getBlockTexture(2));
        }
        else if (index == 12)
        {
            addComponent<LevelBlock>();
            addComponent<Level1Block>();
            std::vector<const sf::Texture *> textures = blockFactory.getQuestionBlockTextures();
            addComponent<Animation>(textures,(int) width, (int)height, 0.3f, true);
        }
        else if (index == 13)
        {
            addComponent<LevelBlock>();
            addComponent<Level2Block>();
            std::vector<const sf::Texture *> textures = blockFactory.getQuestionBlockTextures();
            addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
        }
        else if (index == 14)
        {
            addComponent<LevelBlock>();
            addComponent<Level3Block>();
            std::vector<const sf::Texture *> textures = blockFactory.getQuestionBlockTextures();
            addComponent<Animation>(textures,(int) width, (int)height, 0.3f, true);
        }
        else if (index == 15)
        {
            addComponent<LevelBlock>();
            addComponent<Level4Block>();
            std::vector<const sf::Texture *> textures = blockFactory.getQuestionBlockTextures();
            addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
        }
    }
};