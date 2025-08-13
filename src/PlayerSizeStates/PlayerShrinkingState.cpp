
#include <Gameplay/Player/PlayerSizeStates/PlayerShrinkingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Animation/BlinkingComponent.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerShrinkingState::getName() const
{
    return "Shrinking";
}

void PlayerShrinkingState::onEnter(Entity* entity)
{   
    entity->addComponent<BlinkingComponent>(0.05f);
    
    entity->removeComponent<RigidBody>();
    entity->removeComponent<DamagedTag>();
    entity->removeComponent<CanGetDamageTag>();
}

void PlayerShrinkingState::onExit(Entity* entity)
{  
    entity->removeComponent<BlinkingComponent>();

    entity->addComponent<RigidBody>();
    entity->addComponent<CanGetDamageTag>();

    if (entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        tf.size.y *= 0.5f;
        tf.position.y += tf.size.y;
    }

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 0.5f;
    }
}

std::shared_ptr<PlayerSizeState> PlayerShrinkingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<Animation>())
    {
        auto& anim = entity->getComponent<Animation>();
        if (anim.currentFrame == 2)
        {
            entity->addComponent<RigidBody>();
        }
    }

    if (entity->hasComponent<Animation>())
    {
        auto& anim = entity->getComponent<Animation>();
        if (anim.hasEnded)
        {
            return std::make_shared<PlayerSmallState>();
        }
    }
    return nullptr;
}