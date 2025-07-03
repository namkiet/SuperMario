#include <iostream>
#include "mushroom.h"
using namespace std;

Mushroom::Mushroom(float x, float y, int scale, Handler *handler, UI *ui)
    : Item(x, y, scale, ui, ItemType::Mushroom), handler(handler), ui(ui), originalY(y * scale)
{
    if (ui == nullptr)
    {
        cerr << "UI is null in Mushroom constructor!" << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler is null in Mushroom constructor!" << endl;
        return;
    }

    // Load mushroom texture from UI
    textures = ui->getMushroom1();

    // Set the initial state
    state = MushroomState::Normal;

    // Set the initial speed
    speed = -2.0f;

    // cout << "In Mushroom constructor" << endl;
}

void Mushroom::tick()
{
    ++timeCount;
    applyGravity();
    collision();
    if (isCollected)
    {
        state = MushroomState::Collected;
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
            setVelX(2.0f);
        }
    }

    // Update position based on velocity
    setX(getX() + getVelX());
    setY(getY() + getVelY());
}

void Mushroom::render()
{
    if (state == MushroomState::Normal)
    {
        // cout << getX() << " " << getY() << endl;
        //  cout<< "In Mushroom::render()" << endl;
        DrawTexturePro(textures[0],
                       {0, 0, (float)textures[0].width, (float)textures[0].height},
                       {getX(), getY(), (float)(getWidth()), (float)(getHeight())},
                       {0, 0}, 0.0f, WHITE); // Draw the mushroom texture
    }
    else if (state == MushroomState::Collected)
    {
        return;
    }
}

void Mushroom::playerCollision()
{
    isCollected = true;
}

void Mushroom::blockCollision(GameObject *object)
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
    }

    if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
    {
        setY(object->getY() - getHeight());
        setVelY(0.0f);
    }

    if (CheckCollisionRecs(boundsRight, objectBoundsLeft))
    {
    }

    if (CheckCollisionRecs(boundsLeft, objectBoundsRight))
    {
    }
}

void Mushroom::pipeCollision(GameObject *object)
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

void Mushroom::collision()
{
    const auto &objects = handler->getGameObjects();

    for (auto &object : objects)
    {
        if (object->getID() == GameObject::ObjectID::Block)
        {
            blockCollision(object);
        }
        else if (object->getID() == GameObject::ObjectID::Pipe)
        {
            pipeCollision(object);
        }
        else if (object->getID() == GameObject::ObjectID::Player)
        {
            continue;
        }
    }
}