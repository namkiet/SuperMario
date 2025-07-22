#include <PlayerPowerStates/PlayerGrowingUpState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerGrowingUpState::getName() const
{
    return "GrowingUp";
}

void PlayerGrowingUpState::onEnter(Entity* entity)
{   
    entity->removeComponent<RigidBody>();

    if (entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        tf.position.y -= tf.size.y;
        tf.size.y *= 2.0f;
    }
}

void PlayerGrowingUpState::onExit(Entity* entity)
{  
    entity->addComponent<RigidBody>(sf::Vector2f(0, 0));
    entity->removeComponent<GrowUpTag>();
}

std::shared_ptr<PlayerPowerState> PlayerGrowingUpState::getNewState(Entity* entity)
{
    if (entity->hasComponent<Animation>())
    {
        auto& anim = entity->getComponent<Animation>();
        if (anim.hasEnded)
        {
            return std::make_shared<PlayerBigState>();
        }
    }
    return nullptr;
}