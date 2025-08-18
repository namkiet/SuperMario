#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <iostream>
#include <Gameplay/GameProperties/Components.hpp>

void KoopaSlideState::onEnter(Entity *entity)
{
    entity->addComponent<KoopaSlideTag>();
    entity->addComponent<CanKillEnemyTag>();

    // if (entity->hasComponent<Animation>())
    // {
    //     auto &anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Koopa/koopa_shell.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 16;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0.0f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("koopa_shell"), 16, 16, 1, 0.0f);

    auto &tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaSlideBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 16) * 3.0f;

    auto &patrol = entity->getComponent<KoopaPatrol>();
    patrol.velocity.x = 1000 * (patrol.lastDirection == Direction::Right ? 1 : -1);

    std::vector<Direction> directions = {Direction::Left, Direction::Right, Direction::Bottom};
    entity->addComponent<DamageOnContactComponent>(directions);

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(500);
}

std::shared_ptr<EnemyState> KoopaSlideState::getNewState(Entity *entity, float dt)
{
    timer += dt;
    if (timer > stateDuration)
    {
        entity->addComponent<ChangeToKoopaNormalTag>();
    }

    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
        entity->getComponent<RigidBody>().velocity.y = -300;
        entity->getComponent<RigidBody>().onGround = false;

        entity->getComponent<Transform>().position.y -= 3 * (24 - 16);

        entity->removeComponent<BlockTag>();
        entity->removeComponent<KoopaSlideTag>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToKoopaNormalTag>();
        return std::make_shared<KoopaNormalState>();
    }

    if (entity->hasComponent<ChangeToKoopaShellTag>())
    {
        entity->removeComponent<KoopaSlideTag>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToKoopaShellTag>();
        return std::make_shared<KoopaShellState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<BlockTag>();
        entity->removeComponent<KoopaSlideTag>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}