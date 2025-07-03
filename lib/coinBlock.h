#pragma once
#include "block.h"
#include "coin.h"
enum class CoinBlockState
{
    BeforeHit,
    Hit,
    AfterHit
};

class CoinBlock : public Block
{
private:
    // For animation
    CoinBlockState state;

    // Coin animation
    Coin *coin;

    // For textures
    std::vector<Texture2D> textures;

    // UI pointer
    UI *ui;

    //
    int timeCount = 0;
    int waitingTime = 200; // Time to wait between hits,
                           // if the block is hit again in this interval, timer will be reset
                           // else if the block is hit but the time is run out only allow one more hit

    //
    int hitCount = 12; // Only allow 8 hits to collect the coin

    //  For checking if that block can collect the coin more or not
    bool isCollected = false;

    float originalY; // Store the original Y position of the block

    bool firstTime = true;

public:
    CoinBlock(float x = 0, float y = 0, int width = 0, int height = 0, int index = 0, int scale = 0, UI *ui = nullptr);

    // Update
    void tick() override;
    void render() override;

    void playerCollision(GameObject *object);
};