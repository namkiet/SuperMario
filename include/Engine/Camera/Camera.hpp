#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct Camera : public Component
{
    sf::Vector2f target = {0.0f, 0.0f};   // Smooth-follow target position
};