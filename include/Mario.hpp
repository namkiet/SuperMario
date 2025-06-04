#pragma once

#include <Entity.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y)
    {
        addComponent<Transform>(Transform(x, y));
        addComponent<RigidBody>(RigidBody(300, 0));
        addComponent<Sprite2D>(Sprite2D(sf::Color::Red));
    }
};