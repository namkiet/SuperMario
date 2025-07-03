#pragma once
#include "raylib.h"
#include <vector>
#include "animation.h"
#include "UI.h"

enum class CoinState
{
    CoinForCoinBlock,
    CoinForQuestionBlock,
    Normal,
    Collected
};

class Coin
{
private:
    // For animation
    Animation currentAnimation;
    Animation coinAnimation;

    // Coin textures
    std::vector<Texture2D> coinTextures;

    // Properties
    float x, y;
    int scale;
    int width, height;

    UI *ui;

    // Timer
    int timeCount1 = 0; // Use for draw1
    int timeCount2 = 0; // Use for draw2

    // Coin state
    CoinState state;

public:
    Coin(float x = 0, float y = 0, float width = 0, float height = 0, float scale = 0, UI *ui = nullptr);

    void tick();
    void render();

    void draw1(); // Use for coin block
    void reset();
};