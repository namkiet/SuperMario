#include <iostream>
#include "fire.h"
#include "block.h"
#include "handler.h"
using namespace std;

int Fire::count = 0; // Initialize the static count variable

Fire::Fire(float x, float y, int scale, Handler *handler, UI *ui)
    : Item(x, y, scale, ui, ItemType::Fire), handler(handler), ui(ui)
{
    if (ui == nullptr)
    {
        cerr << "UI pointer is null in Fire constructor." << endl;
        return;
    }

    if (handler == nullptr)
    {
        cerr << "Handler pointer is null in Fire constructor." << endl;
        return;
    }

    // Load fire textures
    fireTextures = ui->getFireBullet(); // Get the fire textures from UI

    currentAnimation = Animation(4, fireTextures); // Initialize the fire animation with a speed of 10

    state = FireState::Normal; // Initialize the fire state

    // Initialize the velocity
    setVelX(10.0f);
    setVelY(5.0f);

    // Initialize the position
    setX(getX() + getWidth());

    // Initialize the width and height
    setWidth(getWidth() / 6);
    setHeight(getHeight() / 6);

    ++count;
}

void Fire::tick()
{
    if (isBoomed)
    {
        // cout << timeCountForBoomed << endl;
        --timeCountForBoomed; // Decrease the time count for boomed state
    }

    applyGravity(); // Apply gravity to the fire object

    if (isBoomed && timeCountForBoomed < 0)
    {
        // cout << "Fire is boomed, setting state to Boomed." << endl;
        state = FireState::Boomed; // If the fire is boomed, set the state to Boomed
    }

    collision();

    setX(getX() + getVelX()); // Update the x position based on velocity
    setY(getY() + getVelY()); // Update the y position based on velocity

    currentAnimation.runAnimation(); // Run the current animation for the fire

    // cout << "Current position of Fire: (" << getX() << ", " << getY() << ") with size: (" << getWidth() << ", " << getHeight() << ")" << endl;
}

void Fire::render()
{
    // cout << "In Fire::render()" << endl;
    currentAnimation.drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight()); // Draw the fire using the current animation
}

void Fire::collision()
{
    const auto &objects = handler->getGameObjects();
    for (auto &object : objects)
    {
        if (object->getID() == ObjectID::Block)
        {
            blockCollision(object);
        }
        else if (object->getID() == ObjectID::Player)
        {
            continue;
        }
    }
}

void Fire::blockCollision(GameObject *object)
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
        // cout << "In Fire::blockCollision() - Stairs block collision detected." << endl;
        if (!isBoomed)
        {
            isBoomed = true;
            timeCountForBoomed = 50;
        }
    }
    else
    {
        if (CheckCollisionRecs(boundsTop, objectBoundsBottom))
        {
            setY(object->getY() + object->getHeight());
            setVelY(0.0f);
        }

        if (CheckCollisionRecs(boundsBottom, objectBoundsTop))
        {
            setY(object->getY() - getHeight() * 2.0f);
            setVelX(10.0f);
            setVelY(-5.0f);
            GameObject::collision();
        }
    }
}

void Fire::enemyCollision()
{
    // Only call in enemy class
}

bool Fire::shouldRemoveItem()
{
    if (state == FireState::Boomed)
    {
        // cout << "In Fire::shouldRemoveItem()" << endl;
        //  cout << "Fire is boomed, removing it." << endl;
        return true;
    }
    else
        return false;
}

bool Fire::isStomped() //
{
    return false; // Fire cannot be stomped
}

Fire::~Fire()
{
    // cout << "Fire object destroyed." << endl;
    --count; // Decrease the count of fire bullets when this object is destroyed
}