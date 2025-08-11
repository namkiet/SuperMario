#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpState.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void BowserJumpState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_jump.png"));
    //     anim.frameWidth = 32;
    //     anim.frameHeight = 35;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Bowser/bowser_jump.png"), 32, 35, 1, 0));

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserJumpBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, -800);
    entity->getComponent<RigidBody>().onGround = false;

    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity.x = 200 * (patrol.lastDirection == Direction::Right ? 1 : -1);
    patrol.velocity.y = 0;

    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom };
    entity->addComponent<DamageOnContactComponent>(directions);
}


std::shared_ptr<EnemyState> BowserJumpState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToBowserWalkTag>())
    {
        entity->removeComponent<ChangeToBowserWalkTag>();
        return std::make_shared<BowserWalkState>();
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

    return nullptr;
}