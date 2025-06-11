#pragma once

#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>

class Enemy : public Entity
{
public:
    Enemy(float x, float y)
    {
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(100.f, 100.f)));
        addComponent<EnemyTag>();
        addComponent<RigidBody>(RigidBody(0, 0));

        sf::Sprite sprite(TextureManager::load("assets/hero_idle.png"));
        addComponent<Sprite2D>(sprite);
        
        addComponent<Transform>(Transform(x, y));
    }
};