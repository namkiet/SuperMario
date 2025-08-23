#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyFlippedBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
void SpinyFlippedState::onEnter(Entity* entity)
{
    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Spiny/spiny_flipped.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 14;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0.25f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("spiny_flipped"), 16, 14, 1, 0.0f);
    
    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<SpinyFlippedBehaviour>();
    
    entity->getComponent<RigidBody>().velocity.y = -600;
    entity->getComponent<SpinyPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<CanHitBlockTag>();
    entity->removeComponent<DamageOnContactComponent>();

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(200);
}

std::shared_ptr<EnemyState> SpinyFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}