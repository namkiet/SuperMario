#include <iostream>
#include "mushroom.h"
#include "block.h"
using namespace std;

Mushroom::Mushroom(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window, MushroomType type)
    : Item(x, y, scale, ui, window, ItemType::Mushroom), handler(handler), originalY(y * scale), type(type)
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
            setVelX(4.0f);
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
        if (type == MushroomType::LevelUp)
        {
            sf::Sprite sprite;
            sprite.setTexture(textures[1]);
            sprite.setPosition(getX(), getY());
            sprite.setScale(getScale(), getScale());
            getWindow().draw(sprite); // Draw the level-up mushroom texture
                                      // cout << "Rendering level-up mushroom at position: (" << getX() << ", " << getY() << ")" << endl;
        }
        else if (type == MushroomType::Normal)
        {
            // Draw the normal mushroom texture
            sf::Sprite sprite;
            sprite.setTexture(textures[0]);
            sprite.setPosition(getX(), getY());
            sprite.setScale(getScale(), getScale());
            getWindow().draw(sprite); // Draw the normal mushroom texture   
        }
    }
    else if (state == MushroomState::Collected)
    {
        return;
    }
}

void Mushroom::playerCollision()
{
    // cout << "Mushroom collected!" << endl;
    isCollected = true;
}

void Mushroom::blockCollision(GameObject *object)
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
    }
    if (boundsTop.intersects(objectBoundsBottom))
    {
        setY(object->getY() + object->getHeight());
        setVelY(0.0f);
    }

    if (boundsBottom.intersects(objectBoundsTop))
    {
        setY(object->getY() - getHeight());
        setVelY(0.0f);
        // cout << "Mushroom position: (" << getX() << ", " << getY() << ")" << endl;
        GameObject::collision();
        // cout << "Mushroom position after trick: (" << getX() << ", " << getY() << ")" << endl;
    }
}

void Mushroom::pipeCollision(GameObject *object)
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

void Mushroom::collision()
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

bool Mushroom::shouldRemoveItem()
{
    // cout << "In Mushroom::shouldRemoveItem()" << endl;
    return state == MushroomState::Collected;
}

bool Mushroom::isStomped()
{
    return isCollected;
}