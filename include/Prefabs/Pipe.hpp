#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Pipe : public Entity
{
public:
    Pipe(float x, float y)
    {
        addComponent<Animation>(Animation(TextureManager::load("assets/pipe.png")));
        addComponent<BoxCollider2D>(sf::Vector2f(SIZE::GRID.x, 2.0f * SIZE::GRID.y));
        addComponent<BlockTag>();
        addComponent<Transform>(sf::Vector2f(x, y), sf::Vector2f(SIZE::GRID.x, 2.0f * SIZE::GRID.y));
    }
};