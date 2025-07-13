#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Piranha : public Entity
{
public:
    Piranha(float x, float y)
    {
        addComponent<Animation>(Animation(TextureManager::load("assets/piranha.png"), 16, 24, 2, 0.25f));

        addComponent<RigidBody>(sf::Vector2f(0, 0), false);
        addComponent<Transform>(sf::Vector2f(x, y), SIZE::GRID);

        addComponent<BoxCollider2D>(SIZE::GRID - sf::Vector2f(10, 10), sf::Vector2f(5, 5));
        addComponent<PassThroughTag>();

        
        std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Top, Direction::Bottom };
        addComponent<DamageOnContactComponent>(directions);
        addComponent<PopupComponent>(2.0f * SIZE::GRID.y, 2.0f);
    }
};