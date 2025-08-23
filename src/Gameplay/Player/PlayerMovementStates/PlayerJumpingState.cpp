#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerJumpingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerRunningState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerClimbingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerShootingState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Entity/Entity.hpp>

const std::string PlayerJumpingState::getName() const
{
    return "Jumping";
}

std::shared_ptr<PlayerMovementState> PlayerJumpingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<RigidBody>())
    {
        auto& rb = entity->getComponent<RigidBody>();
        if (rb.onGround)
        {
            return std::make_shared<PlayerIdlingState>();
        }
    }

    if (entity->hasComponent<ClimbingOnFlagPoleTag>())
    {
        return std::make_shared<PlayerClimbingState>();
    }

    if (entity->hasComponent<ShootingTag>())
    {
        return std::make_shared<PlayerShootingState>();
    }

    return nullptr;
}