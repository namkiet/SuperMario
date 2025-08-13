#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct Camera : public Component
{
    Camera(float trapHalfWidth = 80.0f, float smoothing = 8.0f)
        : trapHalfWidth(trapHalfWidth)
        , smoothing(smoothing)
        , target(0, 0) {}
        
    sf::Vector2f target;
    float trapHalfWidth;
    float smoothing;
};