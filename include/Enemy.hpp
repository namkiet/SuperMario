#pragma once

#include <Entity.hpp>

class Enemy : public Entity
{
public:
    Enemy(float x, float y)
    {
        addComponent<Transform>(Transform(x, y));
        addComponent<RigidBody>(RigidBody(-50, 0));
        addComponent<Sprite2D>(Sprite2D(sf::Color::Blue));
    }
};