#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/Koopa/Components.hpp>
#include <Prefabs/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaNormalState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaShellState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaSlideState.hpp>
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
        anim.sprite = sf::Sprite(TextureManager::load("assets/koopa_walk.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 24;
        anim.frameCount = 2;
        anim.frameDuration = 0.5f;
        anim.currentFrame = 0;
        anim.timer = 0;
    }

    entity->getComponent<RigidBody>().velocity.y = -300;
    entity->getComponent<RigidBody>().onGround = false;

    entity->getComponent<Transform>().position.y -= SIZE::GRID.x/16 * (24 - 16);
    entity->getComponent<Transform>().size = SIZE::GRID.x/16 * sf::Vector2f(16, 24);
    
    entity->getComponent<BoxCollider2D>().size = SIZE::GRID.x/16 * sf::Vector2f(16, 24);

    auto& patrol = entity->getComponent<KoopaPatrol>();
    patrol.velocity.x = 30 * (patrol.lastDirection == Direction::Right ? 1 : -1);

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