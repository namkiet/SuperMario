#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

struct RigidBody : public Component
{
    sf::Vector2f velocity;
    bool applyGravity;
    bool onGround = false;

    RigidBody(sf::Vector2f velocity = sf::Vector2f(0, 0), bool applyGravity = true) 
        : velocity(velocity), applyGravity(applyGravity) {}
};