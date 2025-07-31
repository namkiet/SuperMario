
#include <PlayerPowerStates/PlayerShrinkingState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerShrinkingState::getName() const
{
    return "Shrinking";
}

void PlayerShrinkingState::onEnter(Entity* entity)
{   
    entity->removeComponent<RigidBody>();
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

    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 0.5f;
    }
}

std::shared_ptr<PlayerPowerState> PlayerShrinkingState::getNewState(Entity* entity)
{
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