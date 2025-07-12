#include <iostream>
#include "block.h"
using namespace std;
const float Block::WIDTH = 16.0f;  // Default width of the block
const float Block::HEIGHT = 16.0f; // Default height of the block

Block::Block(int x, int y, int scale, UI *ui, sf::RenderWindow &window, BlockType type)
    : GameObject(x, y, ObjectID::Block, Block::WIDTH, Block::HEIGHT, scale, window, ui),
      index(index), type(type)
{
    // Constructor implementation can be added here if needed
    if (getUI() == nullptr)
    {
        cerr << "UI is null in Block constructor!" << endl;
        return;
    }
    
    // Load block textures from UI
    blockTextures = getUI()->getTile1();

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
    // Turn texture to a sprite and draw it
    sf::Sprite sprite;
    sprite.setTexture(blockTextures[index]);
    sprite.setPosition(getX(), getY());
    sprite.setScale(getScale(), getScale());
    
    getWindow().draw(sprite);
}

sf::FloatRect Block::getBounds()
{
    // cout << "In Block::getBounds()" << endl;
    sf::FloatRect bounds{getX(),
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

sf::FloatRect Block::getBoundsTop()
{
    sf::FloatRect boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 4};
    return boundsTop;
}

sf::FloatRect Block::getBoundsRight()
{
    sf::FloatRect boundsRight{getX() + getWidth() / 2 + getWidth() / 4,
                          getY(),
                          getWidth() / 4,
                          getHeight()};
    return boundsRight;
}

sf::FloatRect Block::getBoundsLeft()
{
    sf::FloatRect boundsLeft{getX(),
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
