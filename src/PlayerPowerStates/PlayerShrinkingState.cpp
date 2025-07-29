
#include <PlayerPowerStates/PlayerShrinkingState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
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
    // entity->removeComponent<InputTag>();

    // if (entity->hasComponent<Transform>())
    // {
    //     auto& tf = entity->getComponent<Transform>();
    //     tf.size.y *= 2.0f;
    //     tf.position.y -= tf.size.y;
    // }

    // if (entity->hasComponent<BoxCollider2D>())
    // {
    //     auto& box = entity->getComponent<BoxCollider2D>();
    //     box.size.y *= 2.0f;
    // }
}

void PlayerShrinkingState::onExit(Entity* entity)
{  
    // entity->addComponent<InputTag>();
    // entity->removeComponent<GrowUpTag>();
}

std::shared_ptr<PlayerPowerState> PlayerShrinkingState::getNewState(Entity* entity)
{
    // if (entity->hasComponent<Animation>())
    // {
    //     auto& anim = entity->getComponent<Animation>();
    //     if (anim.hasEnded)
    //     {
    //         return std::make_shared<PlayerBigState>();
    //     }
    // }
    return nullptr;
}