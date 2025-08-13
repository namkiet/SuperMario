#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserSkidState.hpp>
#include <Gameplay/Enemy/Bowser/BowserSkidBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtState.hpp>
#include <Gameplay/Enemy/Bowser/BowserSlideState.hpp>
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

void BowserSkidState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_skid.png"));
    //     anim.frameWidth = 32;
    //     anim.frameHeight = 35;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_skid"), 32, 35, 1, 0);

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserSkidBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);
    
    auto& towardPlayer = entity->getComponent<TowardPlayer>();
    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity.x = 200 * (towardPlayer.direction == Direction::Left ? 1 : -1);
    patrol.velocity.y = 0;
    patrol.accelerate.x = 300 * (towardPlayer.direction == Direction::Left ? -1 : 1);
    patrol.accelerate.y = 0;

    std::vector<Direction> directions = { Direction::Left, Direction::Right, Direction::Bottom, Direction::Top };
    entity->addComponent<DamageOnContactComponent>(directions);

    entity->removeComponent<StompableTag>();
}


std::shared_ptr<EnemyState> BowserSkidState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToBowserSlideTag>())
    {
        entity->removeComponent<ChangeToBowserSlideTag>();
        return std::make_shared<BowserSlideState>();
    }

    if (entity->hasComponent<ChangeToBowserDeadTag>())
    {
        entity->removeComponent<ChangeToBowserDeadTag>();
        return std::make_shared<BowserDeadState>();
    }

    return nullptr;
}