#include <iostream>
#include <vector>
#include "gameObject.h"
using namespace std;

GameObject::GameObject(float x, float y, ObjectID id, float width, float height, int scale, sf::RenderWindow &window, UI *ui)
    : x(x * scale), y(y * scale), id(id), width(width * scale), height(height * scale), scale(scale), velX(0.0f), velY(0.0f), window(window), ui(ui)
{
    if (id == ObjectID::Player)
        playerScale = scale;
}

GameObject::~GameObject()
{
    // Destructor logic if needed
}

void GameObject::applyGravity()
{
    // cout << "In GameObject::applyGravity()" << endl;
    velY += 0.5f;
}

void GameObject::setX(float x)
{
    // cout << "In GameObject::setX()" << endl;
    this->x = x;
}

void GameObject::setY(float y)
{
    // cout << "In GameObject::setY()" << endl;
    this->y = y;
}

void GameObject::setID(ObjectID id)
{
    // cout << "In GameObject::setID()" << endl;
    this->id = id;
}

void GameObject::setVelX(float velX)
{
    // cout << "In GameObject::setVelX()" << endl;
    this->velX = velX;
}

void GameObject::setVelY(float velY)
{
    // cout << "In GameObject::setVelY()" << endl;
    this->velY = velY;
}

void GameObject::setWidth(float width)
{
    // cout << "In GameObject::setWidth()" << endl;
    this->width = width * scale;
}

void GameObject::setHeight(float height)
{
    // cout << "In GameObject::setHeight()" << endl;
    this->height = height * scale;
}

float GameObject::getX()
{
    // cout << "In GameObject::getX()" << endl;
    return x;
}

float GameObject::getY()
{
    // cout << "In GameObject::getY()" << endl;
    return y;
}

ObjectID GameObject::getID()
{
    // cout << "In GameObject::getID()" << endl;
    return id;
}

float GameObject::getVelX()
{
    // cout << "In GameObject::getVelX()" << endl;
    return velX;
}

float GameObject::getVelY()
{
    // cout << "In GameObject::getVelY()" << endl;
    return velY;
}

float GameObject::getWidth()
{
    // cout << "In GameObject::getWidth()" << endl;
    return width;
}

float GameObject::getHeight()
{
    // cout << "In GameObject::getHeight()" << endl;
    return height;
}

sf::FloatRect GameObject::getBounds()
{
    // cout << "In GameObject::getBounds()" << endl;
    return sf::FloatRect{0, 0, 0, 0};
}

void GameObject::tick()
{
    // cout << "In GameObject::tick()" << endl;
}

void GameObject::render()
{
    // cout << "In GameObject::render()" << endl;
}

int GameObject::getScale()
{
    // cout << "In GameObject::getScale()" << endl;
    return scale;
}

sf::FloatRect GameObject::getBoundsTop()
{
    // cout << "In GameObject::getBoundsTop()" << endl;
    return sf::FloatRect{0, 0, 0, 0};
}

sf::FloatRect GameObject::getBoundsRight()
{
    // cout << "In GameObject::getBoundsRight()" << endl;
    return sf::FloatRect{0, 0, 0, 0};
}

sf::FloatRect GameObject::getBoundsLeft()
{
    // cout << "In GameObject::getBoundsLeft()" << endl;
    return sf::FloatRect{0, 0, 0, 0};
}

void GameObject::showBounds()
{
    // cout << "In GameObject::showBounds()" << endl;
    // This method can be overridden in derived classes to show bounds
}

void GameObject::collision()
{
    // float groundY = 13 * 16 * 3;
    // float bottom = getY() + getHeight();
    // if (bottom > groundY && getY() <= GetScreenHeight())
    // {
    //     setY(groundY - getHeight());
    //     setVelY(0); // Stop downward movement
    // }
}

bool GameObject::isDead()
{
    // cout << "In GameObject::isDead()" << endl;
    return false; // Default implementation, can be overridden in derived classes
}

bool GameObject::isStomped()
{
    // cout << "In GameObject::isStomped()" << endl;
    return false; // Default implementation, can be overridden in derived classes
}

bool GameObject::playerFinishedCollisionChecking()
{
    // cout << "In GameObject::playerFinishedCollisionChecking()" << endl;
    return false; // Default implementation, can be overridden in derived classes
}

void GameObject::setStomped(bool newState)
{
}

void GameObject::setPlayerFinishedCollisionChecking(bool finished)
{
    // cout << "In GameObject::setPlayerFinishedCollisionChecking()" << endl;
    // This method can be overridden in derived classes to set collision checking state
}

void GameObject::setPlayerScale(float scale)
{
    if (id == ObjectID::Player)
    {
        this->y = this->y - this->height * ((scale / this->playerScale) - 1);
        this->height = (this->height / this->playerScale) * scale;
        this->playerScale = scale;
    }
}

float GameObject::getPlayerScale()
{
    if (id == ObjectID::Player)
    {
        return playerScale;
    }
    return scale; // Default scale for non-player objects
}

void GameObject::setScale(int scale)
{
    // cout << "In GameObject::setScale()" << endl;
    this->scale = scale;
    this->width *= scale;
    this->height *= scale;
    this->x *= scale;
    this->y *= scale;
}

UI *GameObject::getUI()
{
    // cout << "In GameObject::getUI()" << endl;
    return ui; // Return the UI pointer
}

sf::RenderWindow &GameObject::getWindow()
{
    // cout << "In GameObject::getWindow()" << endl;
    return window; // Return the window pointer
}