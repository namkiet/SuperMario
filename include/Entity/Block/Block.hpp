#pragma once

#include <Entity/Entity.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/BlockFactory.hpp>

#include <Gameplay/Block/Components.hpp>

#include <ThemeManager.hpp>

#include <vector>

class Block : public Entity
{
public:
    Block(float x, float y, float width, float height, float scale)
    {
        // Add the block tag
        addComponent<BlockTag>();

        // Set the size of the collision box for the block
        addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

        // Set the transform for the player
        addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);
    }
};

class GroundBlock : public Block
{
public: 
    GroundBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<GroundBlockTag>();

        addComponent<Animation>(BlockFactory::getBlockTexture(0));
        getComponent<Animation>().shouldRepeat = true;
    }
};

class StairsBlock : public Block
{
public: 
    StairsBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<StairsBlockTag>();

        addComponent<Animation>(BlockFactory::getBlockTexture(28));
        getComponent<Animation>().shouldRepeat = true;
    }
};

class QuestionBlock : public Block
{
public: 
    QuestionBlock(float x, float y, float width, float height, float scale, int index)
        : Block(x, y, width, height, scale)
    {
        addComponent<QuestionBlockTag>();

        std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
        addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
        
        switch (index)
        {
            case 1:
                addComponent<CoinQuestionBlockTag>();
                break;
            case 2:
                addComponent<MushroomQuestionBlockTag>();
                break;
            case 3:
                addComponent<FlowerQuestionBlockTag>();
                break;
            case 4:
                addComponent<StarQuestionBlockTag>();
                break;
        }
    }
};

class NormalBlock : public Block
{
public: 
    NormalBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<NormalBlockTag>();
        addComponent<Animation>(BlockFactory::getBlockTexture(2));
    }
};

class CoinBlock : public Block
{
public: 
    CoinBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<CoinBlockTag>();
        addComponent<Animation>(BlockFactory::getBlockTexture(2));
        addComponent<CoinBlockComponent>();
    }
};

class LevelUpBlock : public Block
{
public:
    LevelUpBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<LevelUpBlockTag>();
        // bỏ BlockTag vì LevelUp không phải block thường
        removeComponent<BlockTag>();
    }
};

class StarBlock : public Block
{
public:
    StarBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<StarBlockTag>();
        addComponent<Animation>(BlockFactory::getBlockTexture(2));
    }
};

class FlagBlock : public Block
{
public:
    FlagBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<FlagBlockTag>();
        addComponent<Animation>(BlockFactory::getBlockTexture(28));
    }
};

class MushroomBlock : public Block
{
public:
    MushroomBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<MushroomBlockTag>();
        addComponent<Animation>(BlockFactory::getBlockTexture(2));
    }
};

// ---------------- Level Blocks (1–4) ----------------

class LevelBlock : public Block
{
public:
    LevelBlock(float x, float y, float width, float height, float scale)
        : Block(x, y, width, height, scale)
    {
        addComponent<LevelBlockTag>();
    }
};

class Level1Block : public LevelBlock
{
public:
    Level1Block(float x, float y, float width, float height, float scale)
        : LevelBlock(x, y, width, height, scale)
    {
        addComponent<Level1BlockTag>();
        auto textures = BlockFactory::getQuestionBlockTextures();
        addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
    }
};

class Level2Block : public LevelBlock
{
public:
    Level2Block(float x, float y, float width, float height, float scale)
        : LevelBlock(x, y, width, height, scale)
    {
        addComponent<Level2BlockTag>();
        auto textures = BlockFactory::getQuestionBlockTextures();
        addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
    }
};

class Level3Block : public LevelBlock
{
public:
    Level3Block(float x, float y, float width, float height, float scale)
        : LevelBlock(x, y, width, height, scale)
    {
        addComponent<Level3BlockTag>();
        auto textures = BlockFactory::getQuestionBlockTextures();
        addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
    }
};

class Level4Block : public LevelBlock
{
public:
    Level4Block(float x, float y, float width, float height, float scale)
        : LevelBlock(x, y, width, height, scale)
    {
        addComponent<Level4BlockTag>();
        auto textures = BlockFactory::getQuestionBlockTextures();
        addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
    }
};


// class Block : public 
// {
// public:
//     Block(float x, float y, float width, float height, float scale, int index)
//     {
//         // Add the block tag
//         addComponent<BlockTag>();

//         // Set the size of the collision box for the block
//         addComponent<BoxCollider2D>(sf::Vector2f(width, height) * scale);

//         // Set the transform for the player
//         addComponent<Transform>(sf::Vector2f(x, y) * scale, sf::Vector2f(width, height) * scale);

//         // Add different types for different block types
//         if (index < 0)
//         {
//             // Add the ground block tag
//             addComponent<GroundBlockTag>();
//             return;
//         }
//         else if (index == 0)
//         {
//             addComponent<StairsBlockTag>();
//             return;
//         }

//         if (index >= 1 && index <= 4) // Question blocks with animation
//         {
//             addComponent<QuestionBlockTag>();
//             switch (index)
//             {
//             case 1:
//                 addComponent<CoinQuestionBlockTag>();
//                 break;
//             case 2:
//                 addComponent<MushroomQuestionBlockTag>();
//                 break;
//             case 3:
//                 addComponent<FlowerQuestionBlockTag>();
//                 break;
//             case 4:
//                 addComponent<StarQuestionBlockTag>();
//                 break;
//             }

//             std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
//             addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
//         }
//         else if (index == 5) // Normal block
//         {x`
//             addComponent<NormalBlockTag>();
//             addComponent<Animation>(BlockFactory::getBlockTexture(2));
//         }
//         else if (index == 6) // Coin block
//         {
//             addComponent<CoinBlockTag>();
//             addComponent<Animation>(BlockFactory::getBlockTexture(2));
//             addComponent<CoinBlockComponent>();
//         }

//         else if (index == 7) // Stairs block
//         {
//             addComponent<StairsBlockTag>();
//             addComponent<Animation>(BlockFactory::getBlockTexture(28));
//         }
//         else if (index == 8)
//         {
//             // Add the level up block tag
//             addComponent<LevelUpBlockTag>();

//             removeComponent<BlockTag>();
//         }
//         else if (index == 9)
//         {
//             // Add the star block tag
//             addComponent<StarBlockTag>();

//             // Get the texture for the block
//             addComponent<Animation>(BlockFactory::getBlockTexture(2));

//             // std::cout << "star block added" << std::endl;
//         }
//         else if (index == 10) // Flag block
//         {
//             addComponent<FlagBlockTag>();
//             addComponent<Animation>(BlockFactory::getBlockTexture(28));
//         }
//         else if (index == 11)
//         {
//             addComponent<MushroomBlockTag>();
//             addComponent<Animation>(BlockFactory::getBlockTexture(2));
//         }
//         else if (index == 12)
//         {
//             addComponent<LevelBlockTag>();
//             addComponent<Level1BlockTag>();
//             std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
//             addComponent<Animation>(textures,(int) width, (int)height, 0.3f, true);
//         }
//         else if (index == 13)
//         {
//             addComponent<LevelBlockTag>();
//             addComponent<Level2BlockTag>();
//             std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
//             addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
//         }
//         else if (index == 14)
//         {
//             addComponent<LevelBlockTag>();
//             addComponent<Level3BlockTag>();
//             std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
//             addComponent<Animation>(textures,(int) width, (int)height, 0.3f, true);
//         }
//         else if (index == 15)
//         {
//             addComponent<LevelBlockTag>();
//             addComponent<Level4BlockTag>();
//             std::vector<const sf::Texture *> textures = BlockFactory::getQuestionBlockTextures();
//             addComponent<Animation>(textures, (int)width, (int)height, 0.3f, true);
//         }
//     }
// };