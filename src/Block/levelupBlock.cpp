#include <iostream>
#include "levelupBlock.h"
using namespace std;

LevelUpBlock::LevelUpBlock(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window)
    : Block(x, y, scale, ui, window, BlockType::LevelUp), originalY(y * scale), handler(handler), mushroom(nullptr)
{
    if (getUI() == nullptr)
    {
        cerr << "UI is null in LevelUpBlock constructor!" << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in LevelUpBlock constructor!" << endl;
        return;
    }
    
    // Load star textures from UI
    for (int i = 2; i < 4; ++i)
    {
        textures.push_back(getUI()->getTile1()[i]);
    }

    // Set the initial state
    state = LevelUpBlockState::BeforeHit;
}

void LevelUpBlock::tick()
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

    if (isHit() && state == LevelUpBlockState::BeforeHit)
    {
        mushroom = new Mushroom(getX() / getScale(), getY() / getScale(), getScale(), handler, getUI(), getWindow(), MushroomType::LevelUp);
        handler->addObject(mushroom);
        state = LevelUpBlockState::AfterHit;
    }

    if (state == LevelUpBlockState::AfterHit && mushroom)
    {
        mushroom->tick();
    }

    if (isHit())
    {
        state = LevelUpBlockState::AfterHit; // Change state to AfterHit when the block is collected
    }
}

void LevelUpBlock::render()
{
    if (state == LevelUpBlockState::BeforeHit)
    {
        // It will be hidden away
        // DrawTextureEx(textures[0], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the star block texture
    }
    else if (state == LevelUpBlockState::AfterHit)
    {
        sf::Sprite sprite;
        sprite.setTexture(textures[1]);
        sprite.setPosition(getX(), getY());
        sprite.setScale(getScale(), getScale()); // Set the scale of the sprite
getWindow().draw(sprite); // Draw the star block texture after hit
        if (mushroom)
            mushroom->render();
    }
}

void LevelUpBlock::playerCollision(GameObject *object)
{
    if (state == LevelUpBlockState::BeforeHit)
    {
        setY(originalY - getHeight() / 4);
        timeCount = 10; // Set a timer for the bounce effect
    }
}

GameObject *LevelUpBlock::getMushroom()
{
    return mushroom;
}

void LevelUpBlock::setMushroom()
{
    mushroom = nullptr; // Clear the mushroom pointer
}