#include <iostream>
#include "item.h"
using namespace std;

const float Item::WIDTH = 16.0f;  // Example width
const float Item::HEIGHT = 16.0f; // Example height

Item::Item(float x, float y, int scale, UI *ui, sf::RenderWindow &window, ItemType type)
    : GameObject(x, y, ObjectID::Item, Item::WIDTH, Item::HEIGHT, scale, window, ui), type(type)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in Item constructor!" << endl;
        return;
    }
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

sf::FloatRect Item::getBounds()
{
    sf::FloatRect boundsBottom{getX(),
                           getY() + getHeight() / 2,
                           getWidth(),
                           getHeight() / 2};
    return boundsBottom;
}

sf::FloatRect Item::getBoundsTop()
{
    sf::FloatRect boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 2};
    return boundsTop;
}

sf::FloatRect Item::getBoundsRight()
{
    sf::FloatRect boundsRight{getX() + getWidth() / 2,
                          getY(),
                          getWidth() / 2,
                          getHeight()};
    return boundsRight;
}

sf::FloatRect Item::getBoundsLeft()
{
    sf::FloatRect boundsLeft{getX(),
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

void Item::enemyCollision()
{
    // Default implementation, can be overridden in derived classes
    // This is called when an item collides with an enemy
    // For example, a mushroom might grow the player when it collides with an enemy
}