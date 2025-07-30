#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShellState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideState.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlippedBehaviour.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void KoopaFlippedState::onEnter(Entity* entity)
{
    entity->addComponent<KoopaFlippedTag>();
    entity->addComponent<PassThroughTag>();
    entity->removeComponent<CanHitBlockTag>();

    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Koopa/koopa_flipped.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 16;
        anim.frameCount = 1;
        anim.frameDuration = 0.0f;
        anim.currentFrame = 0;
        anim.timer = 0;
    }

    auto& tag = entity->getComponent<EnemyTag>();
    tag.behaviour.reset();
    tag.behaviour = std::make_shared<KoopaFlippedBehaviour>();
    
    entity->getComponent<RigidBody>().velocity.y = -300;
    entity->getComponent<KoopaPatrol>().velocity = sf::Vector2f(0, 0);

    entity->removeComponent<BlockTag>();
    entity->removeComponent<StompableTag>();
    entity->removeComponent<DamageOnContactComponent>();
}

std::shared_ptr<EnemyState> KoopaFlippedState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}