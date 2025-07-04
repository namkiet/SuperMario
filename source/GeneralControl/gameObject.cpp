#include <iostream>
#include <vector>
#include "gameObject.h"
using namespace std;

GameObject::GameObject(float x, float y, ObjectID id, float width, float height, int scale)
    : x(x * scale), y(y * scale), id(id), width(width * scale), height(height * scale), scale(scale), velX(0.0f), velY(0.0f)
{
    // cout << "Game Object constructor called" << endl;
}

GameObject::GameObject(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), x(0.0f), y(0.0f), id(ObjectID::Player),
      width(0.0f), height(0.0f), scale(1), velX(0.0f), velY(0.0f)
{
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

GameObject::ObjectID GameObject::getID()
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

Rectangle GameObject::getBounds()
{
    // cout << "In GameObject::getBounds()" << endl;
    return Rectangle{0, 0, 0, 0};
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

Rectangle GameObject::getBoundsTop()
{
    // cout << "In GameObject::getBoundsTop()" << endl;
    return Rectangle{0, 0, 0, 0};
}

Rectangle GameObject::getBoundsRight()
{
    // cout << "In GameObject::getBoundsRight()" << endl;
    return Rectangle{0, 0, 0, 0};
}

Rectangle GameObject::getBoundsLeft()
{
    // cout << "In GameObject::getBoundsLeft()" << endl;
    return Rectangle{0, 0, 0, 0};
}

void GameObject::showBounds()
{
    // cout << "In GameObject::showBounds()" << endl;
    // This method can be overridden in derived classes to show bounds
}

void GameObject::collision()
{
    // cout << "In GameObject::collision()" << endl;
    // This method can be overridden in derived classes to handle collisions
    // For now, it does nothing
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