#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

void KoopaFlippedState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaFlippedTag>();

    // if (entity->hasComponent<Animation>()) 
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Koopa/koopa_flipped.png"));
    //     anim.frameWidth = 16;
    //     anim.frameHeight = 16;
    //     anim.frameCount = 1;
    //     anim.frameDuration = 0.0f;
    //     anim.currentFrame = 0;
    //     anim.timer = 0;
    // }
    entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("koopa_flipped"), 16, 16, 1, 0.0f);

    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaFlippedBehaviour>();

    entity->getComponent<Transform>().size = sf::Vector2f(16, 16) * 3.0f;
    entity->getComponent<BoxCollider2D>().size = sf::Vector2f(16, 16) * 3.0f;
    
    entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, -500);
    entity->getComponent<KoopaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<CanHitBlockTag>();
    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();

    // Add score tag to notify the score system
    entity->addComponent<ShouldUpdateScore>(200);
}

std::shared_ptr<EnemyState> KoopaFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}