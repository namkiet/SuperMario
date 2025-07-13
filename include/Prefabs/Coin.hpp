#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Coin : public Entity
{
public:
    Coin(float x, float y)
    {
        addComponent<Animation>(Animation(TextureManager::load("assets/coin.png"), 16, 16, 4, 0.125, false));
        addComponent<LifeSpan>(0.5f);
        addComponent<RigidBody>(sf::Vector2f(0, -600));
        addComponent<Transform>(sf::Vector2f(x, y), SIZE::GRID);
    }
};