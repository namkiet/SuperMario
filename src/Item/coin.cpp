#include <iostream>
#include "coin.h"
using namespace std;

Coin::Coin(float x, float y, float scale, UI *ui, sf::RenderWindow &window)
    : Item(x, y, scale, ui, window, ItemType::Coin), timeCount1(0), timeCount2(0)
{
    // cout << "In Coin constructor" << endl;
    if (ui == nullptr)
    {
        cerr << "UI pointer is null in Coin constructor." << endl;
        return;
    }

    // Load textures
    coinTextures = getUI()->getCoin1(); // Get the coin textures from UI

    coinAnimation = new Animation(4, coinTextures, window); // Initialize the coin animation with a speed of 10
    currentAnimation = coinAnimation;                       // Set the current animation to the coin animation

    state = CoinState::Normal; // Initialize the coin state
}

void Coin::tick()
{
    // Update the animation
    ++timeCount1;
    if (timeCount1 >= 20)
    {
        timeCount1 = 0;               // Reset the timer
        state = CoinState::Collected; // Change state to Collected after the animation time
    }
    currentAnimation->runAnimation();
}

void Coin::render()
{
    // Draw the coin at the specified position with the current animation frame
    if (state == CoinState::Collected)
    {
        return; // Do not render if the coin is collected
    }
    else if (state == CoinState::Normal)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight()); // Draw the coin using the current animation
        // DrawTextureEx(coinTextures[3], {x, y}, 0.0f, scale, WHITE); // Draw the first texture of the coin
    }
    else if (state == CoinState::CoinForCoinBlock)
    {
    }
    else if (state == CoinState::CoinForQuestionBlock)
    {
    }
}

void Coin::reset()
{
    state = CoinState::Normal;
    timeCount1 = 0;
}

Coin::~Coin()
{
    if (coinAnimation)
    {
        coinAnimation = nullptr;
    }

    currentAnimation = nullptr;
    coinAnimation = nullptr;
}