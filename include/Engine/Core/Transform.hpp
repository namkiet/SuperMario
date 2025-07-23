#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct Transform : public Component
{
    // sf::Vector2f prevPos;
    sf::Vector2f position;
    sf::Vector2f size;
    bool isFacingRight;

    Transform(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(0, 0), bool isFacingRight = true) 
        : position(position)
        , prevPos(position)
        , size(size)
        , isFacingRight(isFacingRight) {}
};