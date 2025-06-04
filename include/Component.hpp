#pragma once
#include <SFML/Graphics.hpp>

class Component
{
public:
    virtual ~Component() = default;
};

class Transform : public Component
{
public:
    Transform(float x = 0.f, float y = 0.f) : position(x, y) {}

    void setPosition(const sf::Vector2f& vec)
    {
        position = vec;
    }

    void setPosition(float x, float y)
    {
        position = { x, y };
    }

    const sf::Vector2f& getPosition() const
    {
        return position;
    }

private:
    sf::Vector2f position;
};

class RigidBody : public Component
{
public:
    RigidBody(float vx = 0.f, float vy = 0.f) : velocity(vx, vy) {}

    void setVelocity(const sf::Vector2f& vec)
    {
        velocity = vec;
    }

    void setVelocity(float x, float y)
    {
        velocity = { x, y };
    }

    const sf::Vector2f& getVelocity() const
    {
        return velocity;
    }

private:
    sf::Vector2f velocity;
};

class Sprite2D : public Component
{
public:
    Sprite2D(const sf::Color& color) : shape(50.f)
    {
        shape.setFillColor(color);        
    }

    const sf::CircleShape& getShape() const
    {
        return shape;
    }

private:
    sf::CircleShape shape;
};