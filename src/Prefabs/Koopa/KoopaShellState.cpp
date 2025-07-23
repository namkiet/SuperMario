#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/Koopa/Components.hpp>
#include <Prefabs/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaNormalState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaShellState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaSlideState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/TextureManager.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

void KoopaShellState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaShellTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/koopa_shell.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 16;
        anim.frameCount = 2;
        anim.frameDuration = stateDuration / anim.frameCount;
        anim.currentFrame = 0;
        anim.timer = 0;
    }

    entity->getComponent<Transform>().size = SIZE::GRID;
    entity->getComponent<BoxCollider2D>().size = SIZE::GRID;
    entity->getComponent<KoopaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<DamageOnContactComponent>();
}


std::shared_ptr<EnemyState> KoopaShellState::getNewState(Entity* entity, float dt)
{
    timer += dt;
    if (timer > stateDuration)
    {
        entity->addComponent<ChangeToKoopaNormalTag>();
    }

    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaNormalTag>();
        return std::make_shared<KoopaNormalState>();
    }

    if (entity->hasComponent<ChangeToKoopaSlideTag>())
    {
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaSlideTag>();
        return std::make_shared<KoopaSlideState>();
    }

    if (entity->hasComponent<ChangeToKoopaFlippedTag>())
    {
        entity->removeComponent<KoopaShellTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}