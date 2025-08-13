#include <Gameplay/Player/PlayerSizeStates/PlayerGrowingUpState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerBigState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <ECS/Entity.hpp>

PlayerGrowingUpState::PlayerGrowingUpState() : animationDuration(0.7f) {}

const std::string PlayerGrowingUpState::getName() const
{
    return "GrowingUp";
}

void PlayerGrowingUpState::onEnter(Entity* entity)
{   
    entity->removeComponent<GrowUpTag>();
    entity->removeComponent<RigidBody>();

    if (entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        tf.position.y -= tf.size.y;
        tf.size.y *= 2.0f;
    }

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 2.0f;
    }
}

void PlayerGrowingUpState::onExit(Entity* entity)
{  
    entity->addComponent<RigidBody>();
}

void PlayerGrowingUpState::update(Entity* entity, float dt)
{
    animationDuration -= dt;
}

std::shared_ptr<PlayerSizeState> PlayerGrowingUpState::getNewState(Entity* entity)
{
    if (animationDuration < 0.0f)
    {
        return std::make_shared<PlayerBigState>();
    }
    return nullptr;
}