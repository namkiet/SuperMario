#pragma once
#include <SFML/Graphics.hpp>
#include <Component.hpp>

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