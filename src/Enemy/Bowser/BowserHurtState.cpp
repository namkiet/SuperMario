#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtState.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpState.hpp>
#include <Gameplay/Enemy/Bowser/BowserSkidState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void BowserHurtState::onEnter(Entity* entity)
{
    if (entity->hasComponent<Animation>()) 
    {
        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_hurt.png"));
        // anim.frameWidth = 32;
        // anim.frameHeight = 38;
        // anim.frameCount = 2;
        // anim.frameDuration = 0.1f;
        // anim.currentFrame = 0;
        // anim.timer = 0;

        // anim.sprite.setTextureRect(sf::IntRect(
        //     anim.currentFrame * anim.frameWidth,
        //     anim.row * anim.frameHeight,
        //     anim.frameWidth,
        //     anim.frameHeight
        // ));
        entity->addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Bowser/bowser_hurt.png"), 32, 38, 2, 0.1f));
    }

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserHurtBehaviour>();
    
    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity = sf::Vector2f(0, 0);
    patrol.timerDura = 0;
    patrol.timerJump = 0;

    entity->addComponent<StateDuration>();
    auto& stateDur = entity->getComponent<StateDuration>();
    if (entity->getComponent<RigidBody>().onGround == true)
    {
        stateDur.duration = 2;
    }

    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));

    entity->removeComponent<DamageOnContactComponent>();
}


std::shared_ptr<EnemyState> BowserHurtState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToBowserSkidTag>())
    {
        entity->removeComponent<StateDuration>();
        entity->removeComponent<ChangeToBowserSkidTag>();
        return std::make_shared<BowserSkidState>();
    }

    return nullptr;
}