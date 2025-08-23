#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Core/Variables.hpp>
#include <cmath>

struct Camera : public Component
{
    Camera(float trapHalfWidth = 80.0f, float smoothing = 8.0f)
        : trapHalfWidth(trapHalfWidth), smoothing(smoothing), target(SIZE::SCREEN.x / 2, SIZE::SCREEN.y / 2) {}

    sf::Vector2f target;
    float trapHalfWidth;
    float smoothing;
    bool isInScreen(sf::Vector2f pos)
    {
        return std::abs(pos.x - target.x) < SIZE::SCREEN.x / 2 && std::abs(pos.y - target.y) < SIZE::SCREEN.y / 2;
    }
};