#include <iostream>
#include "item.h"
using namespace std;

const float Item::WIDTH = 16.0f;  // Example width
const float Item::HEIGHT = 16.0f; // Example height

Item::Item(float x, float y, int scale, UI *ui, ItemType type)
    : GameObject(x, y, ObjectID::Item, Item::WIDTH, Item::HEIGHT, scale), type(type), ui(ui)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in Item constructor!" << endl;
        return;
    }

    // Load item textures from UI based on type
    // Each item type will load its own textures
}

void Item::tick()
{
}

void Item::render()
{
}

void Item::playerCollision()
{
    // This one is called in player class
}

Rectangle Item::getBounds()
{
    Rectangle boundsBottom{getX(),
                           getY() + getHeight() / 2,
                           getWidth(),
                           getHeight() / 2};
    return boundsBottom;
}

Rectangle Item::getBoundsTop()
{
    Rectangle boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 2};
    return boundsTop;
}

Rectangle Item::getBoundsRight()
{
    Rectangle boundsRight{getX() + getWidth() / 2,
                          getY(),
                          getWidth() / 2,
                          getHeight()};
    return boundsRight;
}

Rectangle Item::getBoundsLeft()
{
    Rectangle boundsLeft{getX(),
                         getY(),
                         getWidth() / 2,
                         getHeight()};
    return boundsLeft;
}

void Item::blockCollision(GameObject *GameObject) {}

void Item::pipeCollision(GameObject *GameObject) {}

bool Item::shouldRemoveItem()
{
    return false; // Default implementation, can be overridden in derived classes
}

bool Item::isStomped()
{
    return false; // Default implementation, can be overridden in derived classes
}

ItemType Item::getItemType()
{
    return type; // Return the item type
}