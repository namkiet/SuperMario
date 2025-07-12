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
    std::vector<sf::Texture> textures;

    // Timer
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
    CoinBlock() = default; // Default constructor

    // Constructor
    CoinBlock(float x, float y, int scale, UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    void playerCollision(GameObject *object);

    ~CoinBlock();
};