#include <iostream>
#include "block.h"
using namespace std;
const float Block::WIDTH = 16.0f;  // Default width of the block
const float Block::HEIGHT = 16.0f; // Default height of the block

Block::Block(int x, int y, int scale, UI *ui, BlockType type)
    : GameObject(x, y, ObjectID::Block, Block::WIDTH, Block::HEIGHT, scale), ui(ui), index(index), type(type)
{
    // Constructor implementation can be added here if needed
    if (ui == nullptr)
    {
        cerr << "UI is null in Block constructor!" << endl;
        return;
    }

    // Load block textures from UI
    blockTextures = ui->getTile1();

    if (type == BlockType::Stairs || type == BlockType::Flag)
    {
        index = 28;
    }
    else if (type == BlockType::Ground)
    {
        index = 0;
    }
    else
    {
        index = 0;
    }
}

void Block::render()
{
    DrawTextureEx(blockTextures[index], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the block texture
}

Rectangle Block::getBounds()
{
    // cout << "In Block::getBounds()" << endl;
    Rectangle bounds{getX(),
                     getY() + getHeight() / 2 + getHeight() / 4,
                     getWidth(),
                     getHeight() / 4};
    return bounds;
}

void Block::setHit()
{
    hit = true;
}

bool Block::shouldRemoveBlock()
{
    return false;
}

Rectangle Block::getBoundsTop()
{
    Rectangle boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 4};
    return boundsTop;
}

Rectangle Block::getBoundsRight()
{
    Rectangle boundsRight{getX() + getWidth() / 2 + getWidth() / 4,
                          getY(),
                          getWidth() / 4,
                          getHeight()};
    return boundsRight;
}

Rectangle Block::getBoundsLeft()
{
    Rectangle boundsLeft{getX(),
                         getY(),
                         getWidth() / 4,
                         getHeight()};
    return boundsLeft;
}

BlockType Block::getBlockID()
{
    return type;
}

bool Block::isHit()
{
    return hit;
}

void Block::playerCollision(GameObject *object)
{
}
