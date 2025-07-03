#include <iostream>
#include "coinBlock.h"
#include "player.h"
using namespace std;

CoinBlock::CoinBlock(float x, float y, int scale, UI *ui)
    : Block(x, y, scale, ui, BlockType::Coin), coin(nullptr), ui(ui), originalY(y * scale)
{
    if (ui == nullptr)
    {
        cerr << "UI pointer is null in CoinBlock constructor." << endl;
        return;
    }

    // For textures
    for (int i = 2; i < 4; ++i)
    {
        textures.push_back(ui->getTile1()[i]); // Load the texture for the coin block
    }
    // Set the initial state
    state = CoinBlockState::BeforeHit;
}

void CoinBlock::tick()
{
    --waitingTime;
    // Block::tick(); // Call the base class tick method
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
        coin = new Coin(getX(), getY() - getHeight() - getHeight() / 4, getScale(), ui); // Create a coin at the block's position
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
        DrawTextureEx(textures[0], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the coin block texture
    }
    else if (state == CoinBlockState::Hit)
    {
        // Render the coin animation when the block is hit
        DrawTextureEx(textures[0], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the coin block texture
        coin->render();
    }
    else if (state == CoinBlockState::AfterHit)
    {
        // cout << "Coin block collected!" << endl;
        DrawTextureEx(textures[1], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the hit coin block texture
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
        delete coin; // Clean up the coin object
        coin = nullptr; // Set to nullptr to avoid dangling pointer
    }
}