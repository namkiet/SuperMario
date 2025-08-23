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
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

void KoopaShellState::onEnter(Entity *entity)
{
    entity->addComponent<KoopaShellTag>();

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

    entity->addComponent<BlockTag>();

    auto &tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaShell_ReviveBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<KoopaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<DamageOnContactComponent>();

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(100);
}

std::shared_ptr<EnemyState> KoopaShellState::getNewState(Entity *entity, float dt)
{
    timer += dt;
    if (timer > stateDuration)
    {
        entity->addComponent<ChangeToKoopaReviveTag>();
    }

    if (entity->hasComponent<ChangeToKoopaReviveTag>())
    {
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaReviveTag>();
        return std::make_shared<KoopaReviveState>();
    }

    if (entity->hasComponent<ChangeToKoopaSlideTag>())
    {
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaSlideTag>();
        return std::make_shared<KoopaSlideState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<BlockTag>();
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}