#include <iostream>
#include "block.h"
using namespace std;

Block::Block(int x, int y, int width, int height, int index, int scale, UI *ui, BlockType type)
    : GameObject(x, y, ObjectID::Block, width, height, scale), ui(ui), index(index), type(type)
{
    // Constructor implementation can be added here if needed
    if (ui == nullptr)
    {
        cerr << "UI is null in Block constructor!" << endl;
        return;
    }

    // Set the position of the block
    positionX = (float)getX();
    positionY = (float)getY();

    // Load block textures from UI
    blockTextures = ui->getTile1();
}

void Block::render()
{
    if (!hit)
        DrawTextureEx(blockTextures[index], {positionX, positionY}, 0.0f, (float)getScale(), WHITE); // Draw the block texture
    else
        debris->draw();
}

void Block::tick()
{
    if (hit)
        debris->tick();
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
    if (ui == nullptr)
    {
        cerr << "UI is null in Block constructor!" << endl;
        return;
    }
    debris = new Debris(getX(), getY(), getWidth(), getHeight(), getScale(), ui);
}

bool Block::shouldRemoveBlock()
{
    // cout << "In Block::shouldRemoveBlock()" << endl;
    if (debris->shouldRemove())
    {
        // cout<< "Debris should be removed." << endl;
        return true; // Remove the block if it has been hit and debris should be removed
    }
    return false; // Keep the block if it is not hit or debris is still visible
}

Block::~Block()
{
    if (debris != nullptr)
    {
        delete debris; // Clean up the debris object
        debris = nullptr;
    }
    // No need to clean up ui, as it is managed by the UI class
    // blockTextures will be cleaned up by raylib when the program exits
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