#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

class Transform : public Component
{
public:
    Transform(float x = 0.f, float y = 0.f, sf::Vector2f size = sf::Vector2f(0, 0)) 
        : position(x, y), size(size) {}

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
    
    void setSize(const sf::Vector2f& sz)
    {
        size = sz;
    }

    const sf::Vector2f& getSize() const
    {
        return size;
    }

private:
    sf::Vector2f position;
    sf::Vector2f size;
};