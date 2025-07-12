#pragma once
#include "block.h"
#include "handler.h"
#include "coin.h"
#include "mushroom.h"
#include "flower.h"
#include "star.h"

enum class QuestionBlockType
{
    Coin,
    Mushroom, // Bigger
    Flower,   // Fire
    Star
};

enum class QuestionBlockState
{
    BeforeHit,
    AfterHit
};
class QuestionBlock : public Block
{
private:
    // For animation
    QuestionBlockState state;
    Animation *normalQuestionBlock;
    Animation *currentAnimation;

    // Question block textures
    std::vector<sf::Texture> questionBlockTextures;

    // For player texture animation
    int index = 0;
    int timeCount = 0;

    float originalY = 0;

    QuestionBlockType type;

    Coin *coin;         // For Coin Question Block
    Mushroom *mushroom; // For Mushroom Question Block
    Flower *flower;     // For Flower Question Block
    Star *star;         // For Star Question Block

    // Handler pointer
    Handler *handler;

public:
    // Constructor
    QuestionBlock() = default; // Default constructor
    QuestionBlock(float x, float y, int scale, Handler *handler,
                  UI *ui, sf::RenderWindow &window, QuestionBlockType type);

    // For updating
    void tick();
    void render();

    void playerCollision(GameObject *object);

    GameObject *getMushroom();
    GameObject *getFlower();
    void setMushroom();
    void setFlower();
    ~QuestionBlock();
};