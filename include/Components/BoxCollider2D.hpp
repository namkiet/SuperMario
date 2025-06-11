#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

class BoxCollider2D : public Component
{
public:
    BoxCollider2D(const sf::Vector2f& size, const sf::Vector2f& offset = sf::Vector2f(0, 0))
        : size(size), offset(offset) {}

    sf::Vector2f size;
    sf::Vector2f offset;
};