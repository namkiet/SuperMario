#pragma once
#include <Entity/Entity.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleBehaviour.hpp>
#include <Factories/EnemyFactory.hpp>

class Bowser : public Entity
{
public:
    Bowser(float x, float y, float scale)
    {
        addComponent<RigidBody>(RigidBody(sf::Vector2f(0, 0)));
        addComponent<Transform>(Transform(sf::Vector2f(x, y) * scale, sf::Vector2f(32, 35) * scale));
        addComponent<BoxCollider2D>(BoxCollider2D(sf::Vector2f(32, 35) * scale));

        addComponent<Animation>(Animation(EnemyFactory::getEnemyTexture("bowser_idle"), 32, 35, 1, 0.0f));

        addComponent<EnemyTag>(std::make_shared<BowserIdleState>(), std::make_shared<BowserIdleBehaviour>());
        addComponent<BowserPatrol>();
        addComponent<BowserAttack>();
        addComponent<TowardPlayer>();

        addComponent<CanHitBlockTag>();
        addComponent<StompableTag>();
        addComponent<Health>(Health(4));

        std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};
        addComponent<DamageOnContactComponent>(directions);
    }
};