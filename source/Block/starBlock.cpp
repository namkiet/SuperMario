#include <iostream>
#include "starBlock.h"
using namespace std;

StarBlock::StarBlock(float x, float y, int scale, Handler *handler, UI *ui)
    : Block(x, y, scale, ui, BlockType::Star), originalY(y * scale), state(StarBlockState::BeforeHit), handler(handler), ui(ui)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in StarBlock constructor!" << endl;
        return;
    }

    // Load star textures from UI
    for (int i = 2; i < 4; ++i)
    {
        textures.push_back(ui->getTile1()[i]);
    }

    // Set the initial state
    state = StarBlockState::BeforeHit;
}

void StarBlock::tick()
{
    // For bounce effect
    if (timeCount > 0)
    {
        --timeCount;
        if (timeCount == 0)
        {
            setY(originalY);
        }
    }

    if (isHit() && state == StarBlockState::BeforeHit)
    {
        star = new Star(getX() / getScale(), getY() / getScale(), getScale(), handler, ui);
        handler->addObject(star);
        state = StarBlockState::AfterHit;
        // cout << "StarBlock hit!" << endl; // Debug message to indicate the block was hit
    }

    if (state == StarBlockState::AfterHit && star)
    {
        // cout << "StarBlock state is AfterHit, updating star animation." << endl; // Debug message
        star->tick();
    }

    if (isHit())
    {
        state = StarBlockState::AfterHit; // Change state to AfterHit when the block is collected
    }
}

void StarBlock::render()
{
    if (state == StarBlockState::BeforeHit)
    {
        DrawTextureEx(textures[0], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the star block texture
    }
    else if (state == StarBlockState::AfterHit)
    {
        DrawTextureEx(textures[1], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the star block after hit
        star->render();                                                               // Render the star animation
    }
}

void StarBlock::playerCollision(GameObject *object)
{
    if (state == StarBlockState::BeforeHit)
    {
        setY(originalY - getHeight() / 4);
        timeCount = 10;
    }
}