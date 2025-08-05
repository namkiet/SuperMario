#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <iostream>

void KoopaNormalState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaNormalTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Koopa/koopa_walk.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 24;
        anim.frameCount = 2;
        anim.frameDuration = 0.5f / 2;
        anim.currentFrame = 0;
        anim.timer = 0;
    }

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaNormalBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 24) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 24) * 3.0f;

    auto& patrol = entity->getComponent<KoopaPatrol>();
    patrol.velocity.x = 60 * (patrol.lastDirection == Direction::Right ? 1 : -1);
    patrol.velocity.y = 0;

    entity->removeComponent<DamageOnContactComponent>();
    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
    entity->addComponent<DamageOnContactComponent>(directions);
}


std::shared_ptr<EnemyState> KoopaNormalState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToKoopaShellTag>())
    {
        entity->removeComponent<KoopaNormalTag>();
        entity->removeComponent<ChangeToKoopaShellTag>();
        return std::make_shared<KoopaShellState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<KoopaNormalTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}