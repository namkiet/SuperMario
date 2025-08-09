#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Lakitu/Components.hpp>
#include <Gameplay/Enemy/Lakitu/LakituFlippedState.hpp>
#include <Gameplay/Enemy/Lakitu/LakituFlippedBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void LakituFlippedState::onEnter(Entity* entity)
{
    entity->addComponent<PassThroughTag>();

    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Lakitu/lakitu_flipped.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 24;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(Animation(TextureManager::load("assets/Enemy/Lakitu/lakitu_flipped.png"), 16, 24, 1, 0));

    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<LakituFlippedBehaviour>();
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, 100);
    entity->getComponent<RigidBody>().applyGravity = true;
    entity->getComponent<LakituPatrol>().velocity = sf::Vector2f(0, 0);
    entity->getComponent<LakituPatrol>().accelerate = 0;

    entity->removeComponent<BlockTag>();
    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();
}

std::shared_ptr<EnemyState> LakituFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}