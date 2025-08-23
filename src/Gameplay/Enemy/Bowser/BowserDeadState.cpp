#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

void BowserDeadState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_dead.png"));
    //     anim.frameWidth = 32;
    //     anim.frameHeight = 39;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_dead"), 32, 39, 1, 0.0f);

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserDeadBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, -900);
    
    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity = sf::Vector2f(0, 0);
    patrol.timerDura = 0;
    patrol.timerJump = 0;

    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/bowserfall.wav"));

    entity->removeComponent<CanHitBlockTag>();
    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(5000);
}

std::shared_ptr<EnemyState> BowserDeadState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}