#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserSlideState.hpp>
#include <Gameplay/Enemy/Bowser/BowserSlideBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpState.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void BowserSlideState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_slide.png"));
    //     anim.frameWidth = 24;
    //     anim.frameHeight = 21;
    //     anim.frameCount = 4;
    //     anim.frameDuration = 0.09f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_slide"), 24, 21, 4, 0.09f);

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserSlideBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);
    entity->getComponent<Transform>().size = sf::Vector2f(24, 21) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(24, 21) * 3.0f;

    auto& towardPlayer = entity->getComponent<TowardPlayer>();
    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.lastDirection = towardPlayer.direction;
    patrol.velocity.x = 1000 * (patrol.lastDirection == Direction::Right ? 1 : -1);
    patrol.velocity.y = 0;

    entity->addComponent<StateDuration>(5);
    entity->addComponent<CanKillEnemyTag>();
    entity->addComponent<SoundComponent>(SoundComponent(&SoundManager::load("assets/Sounds/spin.wav"), true));

    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom, Direction::Top };
    entity->addComponent<DamageOnContactComponent>(directions);

    entity->removeComponent<StompableTag>();
}


std::shared_ptr<EnemyState> BowserSlideState::getNewState(Entity* entity, float dt)
{
    auto& stateDur = entity->getComponent<StateDuration>();
    stateDur.timer += dt;

    if (stateDur.timer > stateDur.duration)
    {
        entity->addComponent<ChangeToBowserWalkTag>();
        entity->getComponent<RigidBody>().velocity.y = -500;
        entity->getComponent<Transform>().position.y -= (35 - 21) * 3;
    }

    if (entity->hasComponent<ChangeToBowserWalkTag>())
    {
        entity->removeComponent<SoundComponent>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToBowserWalkTag>();
        return std::make_shared<BowserWalkState>();
    }

    if (entity->hasComponent<ChangeToBowserDeadTag>())
    {
        entity->removeComponent<SoundComponent>();
        entity->removeComponent<CanKillEnemyTag>();
        entity->removeComponent<ChangeToBowserDeadTag>();
        return std::make_shared<BowserDeadState>();
    }

    return nullptr;
}