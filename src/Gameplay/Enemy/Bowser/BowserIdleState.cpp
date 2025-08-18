#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleState.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkState.hpp>
#include <Gameplay/Enemy/Bowser/BowserDeadState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>

void BowserIdleState::onEnter(Entity* entity)
{

    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_idle.png"));
    //     anim.frameWidth = 32;
    //     anim.frameHeight = 35;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_idle"), 32, 35, 1, 0.0f);

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<BowserIdleBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, 0);

    auto& patrol = entity->getComponent<BowserPatrol>();
    patrol.velocity = sf::Vector2f(0, 0);
    patrol.timerDura = 0;
    patrol.timerJump = 0;
}

std::shared_ptr<EnemyState> BowserIdleState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToBowserWalkTag>())
    {
        entity->removeComponent<ChangeToBowserWalkTag>();
        return std::make_shared<BowserWalkState>();
    }

    if (entity->hasComponent<ChangeToBowserDeadTag>())
    {
        entity->removeComponent<ChangeToBowserDeadTag>();
        return std::make_shared<BowserDeadState>();
    }

    return nullptr;
}