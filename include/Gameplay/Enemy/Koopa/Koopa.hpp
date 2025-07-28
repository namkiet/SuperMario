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
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalBehaviour.hpp>

class Koopa : public Entity
{
public:
    Koopa() = default;
    
    Koopa(float x, float y)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y), SIZE::GRID.x/16 * sf::Vector2f(16, 24)));
        addComponent<BoxCollider2D>(BoxCollider2D(SIZE::GRID.x/16 * sf::Vector2f(16, 24)));

        addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Koopa/koopa_walk.png"), 16, 24, 2, 0.5f / 2));

        addComponent<EnemyTag>(std::make_shared<KoopaNormalState>(), std::make_shared<KoopaNormalBehaviour>());
        addComponent<KoopaPatrol>();
        addComponent<KoopaNormalTag>();
        addComponent<NotOnPatrolYet>();

        addComponent<BlockTag>();
        addComponent<StompableTag>();

        std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
        addComponent<DamageOnContactComponent>(directions);
    }
};