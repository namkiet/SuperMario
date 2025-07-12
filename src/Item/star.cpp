#include <iostream>
#include "star.h"
#include "block.h"
using namespace std;

Star::Star(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window)
    : Item(x, y, scale, ui, window, ItemType::Star), handler(handler), originalY(y * scale)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in Star constructor!" << endl;
        // return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in Star constructor!" << endl;
        return;
    }

    // Load star textures from UI
    textures = ui->getStar1();

    // Set the initial state
    state = StarState::Normal;

    // Set the initial animation
    currentAnimation = new Animation(4, textures, window);

    // cout << "In Star constructor" << endl;

    isCollected = false;
}

void Star::render()
{
    if (state == StarState::Normal)
    {
        // Draw the star using the current animation
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
    }
    else if (state == StarState::Collected)
    {
        return;
    }
}

void Star::tick()
{
    ++timeCount;
    applyGravity();
    collision();
    if (isCollected)
    {
        state = StarState::Collected;
    }
    else
    {
        if (getY() > originalY - getHeight() + getHeight() / 4 && firstTime)
        {
            setVelY(-2.0f);
            setY(getY() + getVelY());
        }
        else if (getY() <= originalY - getHeight() + getHeight() / 4 && firstTime)
        {
            firstTime = false;
            setY(originalY - getHeight() + getHeight() / 4);
            setVelY(0.0f);
            setVelX(4.0f);
        }
        currentAnimation->runAnimation();
    }

    // Update position based on velocity
    setX(getX() + getVelX());
    setY(getY() + getVelY());
}

void Star::collision()
{

    const auto &objects = handler->getGameObjects();

    for (auto &object : objects)
    {
        if (object->getID() == ObjectID::Block)
        {
            blockCollision(object);
        }
        else if (object->getID() == ObjectID::Pipe)
        {
            pipeCollision(object);
        }
        else if (object->getID() == ObjectID::Player)
        {
            continue;
        }
    }
}

void Star::playerCollision()
{
    isCollected = true;
}

void Star::pipeCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    if (boundsTop.intersects(objectBoundsBottom))
    {
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
        return;
    }

    if (boundsBottom.intersects(objectBoundsTop))
    {
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        return;
    }

    if (boundsRight.intersects(objectBoundsLeft))
    {
        setX(object->getX() - getWidth());
        setVelX(-abs(getVelX())); // Move left after hitting right wall
        return;
    }

    if (boundsLeft.intersects(objectBoundsRight))
    {
        setX(object->getX() + object->getWidth());
        setVelX(abs(getVelX())); // Move right after hitting left wall
        return;
    }
}

void Star::blockCollision(GameObject *object)
{
    sf::FloatRect boundsBottom = getBounds();
    sf::FloatRect boundsTop = getBoundsTop();
    sf::FloatRect boundsRight = getBoundsRight();
    sf::FloatRect boundsLeft = getBoundsLeft();

    sf::FloatRect objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    sf::FloatRect objectBoundsTop = object->getBoundsTop();
    sf::FloatRect objectBoundsRight = object->getBoundsRight();
    sf::FloatRect objectBoundsLeft = object->getBoundsLeft();

    Block *block = dynamic_cast<Block *>(object);

    if (block && block->getBlockID() == BlockType::Stairs)
    {
        if (boundsRight.intersects(objectBoundsLeft))
        {
            setX(object->getX() - getWidth());
            setVelX(-abs(getVelX())); // Move left after hitting right wall
        }

        if (boundsLeft.intersects(objectBoundsRight))
        {
            setX(object->getX() + object->getWidth());
            setVelX(abs(getVelX())); // Move right after hitting left wall
        }
    }
    else
    {
        if (boundsTop.intersects(objectBoundsBottom))
        {
            setY(object->getY() + object->getHeight());
            setVelY(0.0f);
        }

        if (boundsBottom.intersects(objectBoundsTop))
        {
            setY(object->getY() - getHeight() * 2.0f);
            setVelX(2.0f);
            setVelY(0.0f);
            GameObject::collision();
        }
    }
}

bool Star::shouldRemoveItem()
{
    return state == StarState::Collected;
}

bool Star::isStomped()
{
    return isCollected;
}

Star::~Star()
{
    if (currentAnimation)
    {
        delete currentAnimation;
        currentAnimation = nullptr;
    }
}