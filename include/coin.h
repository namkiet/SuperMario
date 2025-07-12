#pragma once
#include "item.h"

enum class CoinState
{
    CoinForCoinBlock,
    CoinForQuestionBlock,
    Normal,
    Collected
};

class Coin : public Item
{
private:
    // For animation
    Animation *currentAnimation;
    Animation *coinAnimation;

    // Coin textures
    std::vector<sf::Texture> coinTextures;

    // Timer
    int timeCount1 = 0; // Use for draw1
    int timeCount2 = 0; // Use for draw2

    // Coin state
    CoinState state;

public:
    // Constructor
    Coin() = default;
    Coin(float x, float y, float scale, UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    // Use 1 coin many times
    void reset();

    // Destructor
    ~Coin();
};