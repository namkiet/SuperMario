#include <iostream>
#include "normalBlock.h"
#include "player.h"
using namespace std;

NormalBlock::NormalBlock(float x, float y, int width, int height, int index, int scale, UI *ui)
    : Block(x, y, width, height, index, scale, ui, BlockType::Normal), originalY(y*scale)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in NormalBlock constructor!" << endl;
        return;
    }

    textures.push_back(ui->getTile1()[1]); // Load the texture for the normal block

    state = NormalBlockState::BeforeHit; // Initialize the state to BeforeHit
}

void NormalBlock::tick()
{
    if (timeCount > 0)
    {
        --timeCount;
        if (timeCount == 0)
        {
            setY(originalY);
        }
    }
    if (isHit() && !notBroken)
    {
        state = NormalBlockState::AfterHit;
        Block::tick();
    }
}

void NormalBlock::render()
{
    if (state == NormalBlockState::BeforeHit)
    {
        DrawTextureEx(textures[0], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the block texture
    }
    else if (state == NormalBlockState::AfterHit)
    {
        Block::render();
    }
}

void NormalBlock::playerCollision(GameObject *object)
{
    // Only call this function in player class

    // Cast to player
    Player *player = dynamic_cast<Player *>(object);

    if (player != nullptr && player->isSmallMario())
    {
        notBroken = true;
        // Not break the block but make it a bit higher and back to normal
        setY(originalY - getHeight() / 4);
        timeCount = 10;
    }
    else if (player != nullptr && !player->isSmallMario())
    {
        notBroken = false;
    }
}
