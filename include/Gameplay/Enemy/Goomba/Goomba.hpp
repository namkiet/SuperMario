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
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaNormalState.hpp>
#include <Gameplay/Enemy/Goomba/GoombaBehaviour.hpp>

class Goomba : public Entity
{
public:
    Goomba(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y) * scale, sf::Vector2f(16, 16) * scale));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(16, 16) * scale));

        addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Goomba/goomba_walk.png"), 16, 16, 2, 0.5f / 2));

        addComponent<EnemyTag>(std::make_shared<GoombaNormalState>(), std::make_shared<GoombaBehaviour>());
        addComponent<GoombaPatrol>();
        addComponent<NotOnPatrolYet>();

        addComponent<CanHitBlockTag>();
        addComponent<BlockTag>();
        addComponent<StompableTag>();

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};
        addComponent<DamageOnContactComponent>(directions);
    }
};