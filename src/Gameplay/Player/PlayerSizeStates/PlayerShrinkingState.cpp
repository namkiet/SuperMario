
#include <Gameplay/Player/PlayerSizeStates/PlayerShrinkingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Animation/BlinkingComponent.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Entity/Entity.hpp>

const std::string PlayerShrinkingState::getName() const
{
    return "Shrinking";
}

void PlayerShrinkingState::onEnter(Entity* entity)
{   
    entity->addComponent<BlinkingComponent>(0.05f, 2.5f);
    entity->removeComponent<RigidBody>();
    entity->removeComponent<DamagedTag>();
    entity->removeComponent<CanGetDamageTag>();
    entity->removeComponent<CanFireTag>();
}

void PlayerShrinkingState::onExit(Entity* entity)
{  
    entity->addComponent<RigidBody>();

    if (entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        tf.size.y *= 0.5f;
        tf.position.y += tf.size.y;
    }

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.offset.x += 6.0f;
        box.size.x -= 12.0f;
        box.size.y *= 0.5f;
    }
}

std::shared_ptr<PlayerSizeState> PlayerShrinkingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<Animation>() && entity->getComponent<Animation>().hasEnded)
    {
        return std::make_shared<PlayerSmallState>();
    }

    return nullptr;
}