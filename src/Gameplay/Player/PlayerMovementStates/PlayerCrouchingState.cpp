#include <Gameplay/Player/PlayerMovementStates/PlayerCrouchingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerRunningState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <ECS/Entity.hpp>
#include <Core/KeyPressPool.hpp>

const std::string PlayerCrouchingState::getName() const
{
    return "Crouching";
}

void PlayerCrouchingState::onEnter(Entity* entity)
{
    if (entity->hasComponent<BoxCollider2D>() && entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 0.5f;
        box.offset.y += box.size.y;
        // tf.position.y += box.size.y;
    }
}

void PlayerCrouchingState::onExit(Entity* entity)
{
    if (entity->hasComponent<BoxCollider2D>() && entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        auto& box = entity->getComponent<BoxCollider2D>();
        // tf.position.y -= box.size.y;
        box.offset.y -= box.size.y;
        box.size.y *= 2.0f;
    }
}

std::shared_ptr<PlayerMovementState> PlayerCrouchingState::getNewState(Entity* entity)
{
    if (!KeyPressPool::Instance().isKeyPressed(sf::Keyboard::S)) 
    {
        return std::make_shared<PlayerIdlingState>();
    }

    if (entity->hasComponent<RigidBody>() && entity->getComponent<RigidBody>().velocity.x != 0.0f)
    {
        return std::make_shared<PlayerRunningState>();
    }

    return nullptr;
}