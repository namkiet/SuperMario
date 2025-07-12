#include <iostream>
#include "fire.h"
#include "block.h"
#include "handler.h"
using namespace std;

int Fire::count = 0; // Initialize the static count variable

Fire::Fire(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window)
    : Item(x, y, scale, ui, window, ItemType::Fire), handler(handler)
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
    fireTextures = getUI()->getFireBullet(); // Get the fire textures from UI

    // cout << "Size of fireTextures: " << fireTextures.size() << endl;

    // Temporary vector to hold the fire textures
    std::vector<sf::Texture> tempFireTextures;
    for (int i = 0; i < 4; ++i)
    {
        tempFireTextures.push_back(fireTextures[i]); //
    }

    currentAnimation = new Animation(2, tempFireTextures, window); // Initialize the fire animation with a speed of 10

    state = FireState::Normal; // Initialize the fire state

    if (handler->getPlayer()->isPlayerForward() || handler->getPlayer()->getVelX() > 0)
    {
        // Initialize the velocity
        setVelX(10.0f);
        // Initialize the position
        setX(getX() + getWidth());
    }
    else if (!handler->getPlayer()->isPlayerForward() || handler->getPlayer()->getVelX() < 0)
    {
        // Initialize the velocity
        setVelX(-10.0f);
    }

    setVelY(5.0f);

    // Initialize the width and height
    setWidth(getWidth() / 6);
    setHeight(getHeight() / 6);

    // Initialize the timer
    timeCountForNormal = 0;
    timeCountForBoomed = 0;

    // Increase the count of fire bullets
    ++count;
}

void Fire::tick()
{
    // Update the timers
    ++timeCountForNormal; // Decrease the time count for normal state
    --timeCountForBoomed; // Decrease the time count for boomed state

    // Apply gravity to the fire object
    applyGravity(); // Apply gravity to the fire object

    //
    if (isBoomed && renderNormalFinished)
    {
        // cout << "Fire is boomed, setting state to Boomed." << endl;
        state = FireState::Boomed; // If the fire is boomed, set the state to Boomed
    }

    collision();

    setX(getX() + getVelX()); // Update the x position based on velocity
    setY(getY() + getVelY()); // Update the y position based on velocity

    currentAnimation->runAnimation(); // Run the current animation for the fire

    // cout << "Current position of Fire: (" << getX() << ", " << getY() << ") with size: (" << getWidth() << ", " << getHeight() << ")" << endl;
}

void Fire::render()
{
    if (state == FireState::Normal)
    {
        currentAnimation->drawAnimation(getX(), getY(), (float)getWidth(), (float)getHeight()); // Draw the fire using the current animation
        if (!renderNormalFinished)
        {
            if (timeCountForNormal >= 10)
            {
                renderNormalFinished = true;
            }
        }
    }
    else if (state == FireState::Boomed)
    {
        sf::Sprite sprite;
        sprite.setTexture(fireTextures[4]); // Set the boomed texture
        sprite.setPosition(getX(), getY());
        float scaleX = (getWidth() * 2) / fireTextures[4].getSize().x;  // Scale the sprite based on the texture size
        float scaleY = (getHeight() * 2) / fireTextures[4].getSize().y; // Scale the sprite based on the texture size
        sprite.setScale(scaleX, scaleY);                                // Set the scale of the sprite
        getWindow().draw(sprite);                                       // Draw the boomed fire texture

        // Only set once when the fire is boomed
        if (!renderBoomedFinished)
            timeCountForBoomed = 10;

        renderBoomedFinished = true; // Set renderFinished to true when the fire is boomed
    }
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

void Fire::blockCollision(GameObject *object)
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
    // if (block)
    //     cout << (int)block->getBlockID() << endl;

    if (block && block->getBlockID() == BlockType::Stairs)
    {
        // cout << "In Fire::blockCollision() - Stairs block collision detected." << endl;
        // cout << getX() << " " << getY() << " " << getWidth() << " " << getHeight() << endl;
        if (boundsTop.intersects(objectBoundsBottom) || boundsBottom.intersects(objectBoundsTop) ||
            boundsRight.intersects(objectBoundsLeft) || boundsLeft.intersects(objectBoundsRight))
        {
            if (!isBoomed)
            {
                isBoomed = true;
                // cout << "Fire is boomed!" << endl;
                // timeCountForBoomed = 10; // Set the time count for boomed state
            }
        }
    }
    else if (block && block->getBlockID() != BlockType::Stairs)
    {
        if (boundsTop.intersects(objectBoundsBottom))
        {
            setY(object->getY() + object->getHeight());
            setVelY(0.0f);
        }

        if (boundsBottom.intersects(objectBoundsTop))
        {
            setY(object->getY() - getHeight() * 2.0f);
            if (handler->getPlayer()->isPlayerForward() || handler->getPlayer()->getVelX() > 0)
            {
                setVelX(10.0f);
            }
            else if (!handler->getPlayer()->isPlayerForward() || handler->getPlayer()->getVelX() < 0)
            {
                setVelX(-10.0f);
            }
            setVelY(-5.0f);
            GameObject::collision();
        }
    }
}

void Fire::pipeCollision(GameObject *object)
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
        if (!isBoomed)
            isBoomed = true;
    }
}

void Fire::enemyCollision()
{
    // Only call in enemy class

    if (!isBoomed)
    {
        isBoomed = true;
    }
}

bool Fire::shouldRemoveItem()
{
    if (state == FireState::Boomed && renderBoomedFinished && timeCountForBoomed <= 0)
    {
        // cout << "In Fire::shouldRemoveItem()" << endl;
        //  cout << "Fire is boomed, removing it." << endl;
        return true;
    }
    else
        return false;
}

bool Fire::isStomped() // I just call like this but it is just for checking if the fire is boomed and cant use that for another purpose
{
    return isBoomed;
}

Fire::~Fire()
{
    --count;
    if (currentAnimation)
    {
        delete currentAnimation;
        currentAnimation = nullptr;
    }
}