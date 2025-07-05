#pragma once
#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Coin : public Entity
{
public:
    Coin(float x, float y)
    {
        BoxCollider2D box(SIZE::GRID);
        box.isSolid = false;

        addComponent<Animation>(Animation(TextureManager::load("assets/coin.png"), 16, 16, 4, 0.125, false));
        addComponent<BoxCollider2D>(box);
        addComponent<CollectibleTag>();
        addComponent<LifeSpan>(0.5f);
        addComponent<Transform>(Transform(sf::Vector2f(x, y), SIZE::GRID));
    }
};