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
    Animation currentAnimation;
    Animation coinAnimation;

    // Coin textures
    std::vector<Texture2D> coinTextures;

    // Properties

    // UI pointer
    UI *ui;

    // Timer
    int timeCount1 = 0; // Use for draw1
    int timeCount2 = 0; // Use for draw2

    // Coin state
    CoinState state;

public:
    // Constructor
    Coin(float x = 0, float y = 0, float scale = 0, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    // Use 1 coin many times
    void reset();
};