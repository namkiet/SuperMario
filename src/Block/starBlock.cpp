#include <iostream>
#include "starBlock.h"
using namespace std;

StarBlock::StarBlock(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window)
    : Block(x, y, scale, ui, window, BlockType::Star), originalY(y * scale), handler(handler), star(nullptr)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in StarBlock constructor!" << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in StarBlock constructor!" << endl;
        return;
    }

    // Load star textures from UI
    for (int i = 2; i < 4; ++i)
    {
        textures.push_back(getUI()->getTile1()[i]);
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
        star = new Star(getX() / getScale(), getY() / getScale(), getScale(), handler, getUI(), getWindow());
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
        sf::Sprite sprite;
        sprite.setTexture(textures[0]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale()); // Set the scale of the sprite
        getWindow().draw(sprite); // Draw the before-hit star block texture
    }
    else if (state == StarBlockState::AfterHit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[1]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale()); // Set the scale of the sprite
        getWindow().draw(sprite); // Draw the after-hit star block texture
        if (star)
            star->render(); // Render the star animation
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

GameObject *StarBlock::getStar()
{
    return star;
}

void StarBlock::setStar()
{
    star = nullptr;
}