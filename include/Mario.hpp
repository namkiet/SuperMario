#pragma once

#include <Entity.hpp>
#include <Components/Declaration.hpp>

class Mario : public Entity
{
public:
    Mario(float x, float y)
    {
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(100.f, 100.f)));
        addComponent<Gravity>(Gravity(90.f));
        addComponent<Input>();
        addComponent<RigidBody>(RigidBody(0, 0));
        addComponent<Sprite2D>(Sprite2D(sf::Color::Red));
        addComponent<Transform>(Transform(x, y));
    }
};