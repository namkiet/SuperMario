#pragma once
#include <ECS/Entity.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlyingState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlyingBehaviour.hpp>

class KoopaFlying : public Entity
{
public:
    KoopaFlying() = default;
    
    KoopaFlying(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y), sf::Vector2f(16 * scale, 24 * scale)));
        addComponent<BoxCollider2D>(BoxCollider2D(SIZE::GRID.x/16 * sf::Vector2f(16, 24)));

        addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Koopa/koopa_fly.png"), 16, 24, 2, 0.5f / 2));

        addComponent<EnemyTag>(std::make_shared<KoopaFlyingState>(), std::make_shared<KoopaFlyingBehaviour>());
        addComponent<KoopaPatrol>();
        addComponent<KoopaFlyingPatrol>();
        addComponent<KoopaFlyingTag>();
        addComponent<NotOnPatrolYet>();

        addComponent<BlockTag>();
        addComponent<StompableTag>();

        std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
        addComponent<DamageOnContactComponent>(directions);
    }
};