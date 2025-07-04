#include <iostream>
#include "star.h"
#include "block.h"
using namespace std;

Star::Star(float x, float y, int scale, Handler *handler, UI *ui)
    : Item(x, y, scale, ui, ItemType::Star), handler(handler), ui(ui), originalY(y * scale)
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
    currentAnimation = Animation(4, textures);

    // cout << "In Star constructor" << endl;

    isCollected = false;
}

void Star::render()
{
    if (state == StarState::Normal)
    {
        // Draw the star using the current animation
        currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight());
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
        currentAnimation.runAnimation();
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
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    if (CheckCollisionRecs(boundsTop, objectBoundsBottom))
    {
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
        return;
    }

    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        return;
    }

    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
        setX(object->getX() - getWidth());
        setVelX(-abs(getVelX())); // Move left after hitting right wall
        return;
    }

    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
        setX(object->getX() + object->getWidth());
        setVelX(abs(getVelX())); // Move right after hitting left wall
        return;
    }
}

void Star::blockCollision(GameObject *object)
{
    Rectangle boundsBottom = getBounds();
    Rectangle boundsTop = getBoundsTop();
    Rectangle boundsRight = getBoundsRight();
    Rectangle boundsLeft = getBoundsLeft();

    Rectangle objectBoundsBottom = object->getBounds(); // Get the lower 1/4 bounds of the object
    Rectangle objectBoundsTop = object->getBoundsTop();
    Rectangle objectBoundsRight = object->getBoundsRight();
    Rectangle objectBoundsLeft = object->getBoundsLeft();

    Block *block = dynamic_cast<Block *>(object);

    if (block && block->getBlockID() == BlockType::Stairs)
    {
        if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
        {
            setX(object->getX() - getWidth());
            setVelX(-abs(getVelX())); // Move left after hitting right wall
        }

        if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
        {
            setX(object->getX() + object->getWidth());
            setVelX(abs(getVelX())); // Move right after hitting left wall
        }
    }
    else
    {
    }
    if (CheckCollisionRecs(boundsTop, objectBoundsBottom))
    {
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
    }

    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        GameObject::collision();
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