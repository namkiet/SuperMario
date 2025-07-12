#include <iostream>
#include "flower.h"
using namespace std;

Flower::Flower(float x, float y, int scale, UI *ui, sf::RenderWindow &window)
    : Item(x, y, scale, ui, window, ItemType::Flower)
{
    if (ui == nullptr)
    {
        cerr << "UI pointer is null in Flower constructor." << endl;
        return;
    }

    // Load flower textures from UI
    textures = ui->getFlower1();

    // Set the initial state
    state = FlowerState::Normal;

    // Initialize the current animation
    currentAnimation = new Animation(4, textures, window);
}

void Flower::tick()
{
    if (isCollected)
    {
        state = FlowerState::Collected;
    }
    else
    {
        currentAnimation->runAnimation();
    }
}

void Flower::render()
{
    if (state == FlowerState::Normal)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == FlowerState::Collected)
    {
        return;
    }
}

void Flower::playerCollision()
{
    isCollected = true;
}

bool Flower::shouldRemoveItem()
{
    return state == FlowerState::Collected;
}

bool Flower::isStomped() // meaning that the flower is collected
{
    return isCollected;
}

Flower::~Flower()
{
    if (currentAnimation)
    {
        delete currentAnimation;
        currentAnimation = nullptr;
    }
}
