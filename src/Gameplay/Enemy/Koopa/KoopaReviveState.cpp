#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaReviveState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShell_ReviveBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

void KoopaReviveState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaReviveTag>();

    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Koopa/koopa_revive.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 16;
    //     anim.frameCount = 2;
    //     anim.frameDuration = stateDuration / anim.frameCount / 9;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("koopa_revive"), 16, 16, 2, stateDuration / 2 / 9);

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaShell_ReviveBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<KoopaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<DamageOnContactComponent>();
}


std::shared_ptr<EnemyState> KoopaReviveState::getNewState(Entity* entity, float dt)
{
    timer += dt;
    if (timer > stateDuration)
    {
        entity->addComponent<ChangeToKoopaNormalTag>();

        entity->getComponent<RigidBody>().velocity.y = -300;
        entity->getComponent<RigidBody>().onGround = false;

        entity->getComponent<Transform>().position.y -= 3 * (24 - 16);
    }

    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
        entity->removeComponent<BlockTag>();
        entity->removeComponent<KoopaReviveTag>();
        entity->removeComponent<ChangeToKoopaNormalTag>();
        return std::make_shared<KoopaNormalState>();
    }

    if (entity->hasComponent<ChangeToKoopaShellTag>())
    {
        entity->removeComponent<KoopaReviveTag>();
        entity->removeComponent<ChangeToKoopaShellTag>();
        return std::make_shared<KoopaShellState>();
    }

    if (entity->hasComponent<ChangeToKoopaSlideTag>())
    {
        entity->removeComponent<KoopaReviveTag>();
        entity->removeComponent<ChangeToKoopaSlideTag>();
        return std::make_shared<KoopaSlideState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<BlockTag>();
        entity->removeComponent<KoopaReviveTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}