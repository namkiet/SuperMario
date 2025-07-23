#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/Koopa/Components.hpp>
#include <Prefabs/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaNormalState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaShellState.hpp>
#include <Prefabs/Enemy/Koopa/KoopaSlideState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>

void KoopaSlideState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaSlideTag>();
    entity->addComponent<CanKillEnemyTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/koopa_slide.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 16;
        anim.frameCount = 1;
        anim.frameDuration = 0.0f;
    }

    auto& patrol = entity->getComponent<KoopaPatrol>();
    patrol.velocity.x = 800 * (patrol.lastDirection == Direction::Right ? 1 : -1);

    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
    entity->addComponent<DamageOnContactComponent>(directions);
}


std::shared_ptr<EnemyState> KoopaSlideState::getNewState(Entity* entity, float dt)
{
    timer += dt;
    if (timer > stateDuration)
    {
        entity->addComponent<ChangeToKoopaNormalTag>();
    }

    if (entity->hasComponent<ChangeToKoopaNormalTag>())
    {
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
        entity->removeComponent<KoopaSlideTag>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToKoopaFlippedTag>();
        return std::make_shared<KoopaFlippedState>();
    }

    return nullptr;
}