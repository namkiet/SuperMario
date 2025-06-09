#pragma once
#include <SFML/Graphics.hpp>
#include <Component.hpp>

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