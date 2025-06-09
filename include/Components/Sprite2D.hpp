#pragma once
#include <SFML/Graphics.hpp>
#include <Component.hpp>

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