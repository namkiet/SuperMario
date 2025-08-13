
#include <Gameplay/Player/PlayerSizeStates/PlayerShrinkingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Animation/BlinkingComponent.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <ECS/Entity.hpp>

PlayerShrinkingState::PlayerShrinkingState() : animationDuration(3.0f), animationTimer(0.0f) {}

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

void PlayerShrinkingState::update(Entity* entity, float dt)
{
    animationTimer += dt;
}

std::shared_ptr<PlayerSizeState> PlayerShrinkingState::getNewState(Entity* entity)
{
    if (animationTimer >= animationDuration)
    {
        return std::make_shared<PlayerSmallState>();
    }

    if (animationTimer >= 0.5f * animationDuration)
    {
        if (!entity->hasComponent<RigidBody>())
        {
            entity->addComponent<RigidBody>();
        }
    }

    return nullptr;
}