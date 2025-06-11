#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct Camera : public Component 
{
    sf::Vector2f position = {0.0f, 0.0f};  // World position (center of view)
    sf::Vector2f size     = {800.0f, 600.0f};  // View size (e.g. screen size)
    sf::Vector2f target   = {0.0f, 0.0f};  // Smooth-follow target position

    float smoothing = 0.0f;  // 0.0 = instant, 1.0 = no movement

    void update(float dt) {
        position += (target - position) * smoothing;
    }

    sf::Vector2f getTopLeft() const {
        return position - size / 2.0f;
    }
};