#include <iostream>
#include "coinBlock.h"
#include "player.h"
using namespace std;

CoinBlock::CoinBlock(float x, float y, int scale, UI *ui, sf::RenderWindow &window)
    : Block(x, y, scale, ui, window, BlockType::Coin), coin(nullptr), originalY(y * scale)
{
    if (getUI() == nullptr)
    {
        cerr << "UI pointer is null in CoinBlock constructor." << endl;
        return;
    }

    // For textures
    for (int i = 2; i < 4; ++i)
    {
        textures.push_back(getUI()->getTile1()[i]); // Load the texture for the coin block
    }
    // Set the initial state
    state = CoinBlockState::BeforeHit;
}

void CoinBlock::tick()
{
    --waitingTime;

    // For bounce effect
    if (timeCount > 0)
    {
        --timeCount;
        if (timeCount == 0)
        {
            setY(originalY);
        }
    }

    if (isHit() && state == CoinBlockState::BeforeHit)
    {
        // Create a coin at the block's position
        coin = new Coin(getX() / getScale(), (getY() - getHeight() - getHeight() / 4) / getScale(), getScale(), getUI(), getWindow());

        // Set the state to Hit
        state = CoinBlockState::Hit;
    }
    if (state == CoinBlockState::Hit && coin)
    {
        coin->tick();
    }

    if (isCollected)
    {
        // cout << "Here" << endl;
        state = CoinBlockState::AfterHit; // Change state to AfterHit when the block is collected
    }
}

void CoinBlock::render()
{
    if (state == CoinBlockState::BeforeHit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[0]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale());
        getWindow().draw(sprite); // Draw the coin block texture before hit
    }
    else if (state == CoinBlockState::Hit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[0]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale());
        getWindow().draw(sprite); // Draw the coin block texture after hit
        coin->render();
    }
    else if (state == CoinBlockState::AfterHit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[1]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale());
        getWindow().draw(sprite); // Draw the coin block texture after collection
    }
}

void CoinBlock::playerCollision(GameObject *object)
{
    // Only call this function in player class
    Player *player = dynamic_cast<Player *>(object);

    if (player != nullptr && !isCollected)
    {
        if (hitCount > 0 && waitingTime <= 0 && !firstTime)
        {
            hitCount = 1; // Allow only one more hit if the waiting time is over
        }
        --hitCount;
        waitingTime = 200;
        if (coin)
            coin->reset();
    }

    if (firstTime)
    {
        firstTime = false;
    }

    if (hitCount == 0)
    {
        isCollected = true;
    }

    if (state != CoinBlockState::AfterHit)
    {
        setY(originalY - getHeight() / 4);
        timeCount = 10;
    }
}

CoinBlock::~CoinBlock()
{
    if (coin != nullptr)
    {
        delete coin;    // Clean up the coin object
        coin = nullptr; // Set to nullptr to avoid dangling pointer
    }
}