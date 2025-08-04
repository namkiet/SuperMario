#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpState.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void BowserWalkState::onEnter(Entity* entity)
{
    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_walk.png"));
        anim.frameWidth = 32;
        anim.frameHeight = 35;
        anim.frameCount = 4;
        anim.frameDuration = 0.25f;
        anim.currentFrame = 0;
        anim.timer = 0;

        anim.sprite.setTextureRect(sf::IntRect(
            anim.currentFrame * anim.frameWidth,
            anim.row * anim.frameHeight,
            anim.frameWidth,
            anim.frameHeight
        ));
    }

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserWalkBehaviour>();
    
    entity->getComponent<Transform>().size = sf::Vector2f(32, 35) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(32, 35) * 3.0f;

    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity.x = 30 * (patrol.lastDirection == Direction::Right ? 1 : -1);
    patrol.velocity.y = 0;

    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
    entity->removeComponent<DamageOnContactComponent>();
    entity->addComponent<DamageOnContactComponent>(directions);
}


std::shared_ptr<EnemyState> BowserWalkState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToBowserJumpTag>())
    {
        entity->removeComponent<ChangeToBowserJumpTag>();
        return std::make_shared<BowserJumpState>();
    }

    if (entity->hasComponent<ChangeToBowserHurtTag>())
    {
        entity->removeComponent<ChangeToBowserHurtTag>();
        return std::make_shared<BowserHurtState>();
    }

    if (entity->hasComponent<ChangeToBowserDeadTag>())
    {
        entity->removeComponent<ChangeToBowserDeadTag>();
        return std::make_shared<BowserDeadState>();
    }

    if (entity->hasComponent<ChangeToBowserIdleTag>())
    {
        entity->removeComponent<ChangeToBowserIdleTag>();
        return std::make_shared<BowserIdleState>();
    }

    return nullptr;
}