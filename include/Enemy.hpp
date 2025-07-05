#pragma once
#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Enemy : public Entity
{
public:
    Enemy(float x, float y)
    {
        addComponent<Animation>(Animation(TextureManager::load("assets/goomba.png"), 16, 16, 2, 0.5f / 2));
        addComponent<BoxCollider2D>(BoxCollider2D(0.5f * SIZE::GRID));
        addComponent<EnemyTag>();
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y), 0.5f * SIZE::GRID));
    }
};