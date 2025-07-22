#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Fireball/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>

class Enemy : public Entity
{
public:
    Enemy(float x, float y)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y), SIZE::GRID));
        addComponent<BoxCollider2D>(BoxCollider2D(SIZE::GRID));

        addComponent<Animation>(Animation(TextureManager::load("assets/goomba.png"), 16, 16, 2, 0.5f / 2));


        addComponent<CanHitBlockTag>();

        addComponent<PatrolComponent>();
        addComponent<StompableTag>();

        std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
        addComponent<DamageOnContactComponent>(directions);

        addComponent<FlammableTag>();
    }
};