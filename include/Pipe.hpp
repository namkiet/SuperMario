#pragma once
#include <ECS/Entity.hpp>
#include <Components/Declaration.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Pipe : public Entity
{
public:
    Pipe(float x, float y)
    {
        addComponent<Animation>(Animation(TextureManager::load("assets/pipe.png")));
        addComponent<BoxCollider2D>(sf::Vector2f(SIZE::GRID.x, 2.0f * SIZE::GRID.y));
        addComponent<BlockTag>("Pipe");
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(SIZE::GRID.x, 2.0f * SIZE::GRID.y));
    }
};