#include <PlayerMovementStates/PlayerIdlingState.hpp>
#include <PlayerMovementStates/PlayerJumpingState.hpp>
#include <PlayerMovementStates/PlayerRunningState.hpp>
#include <PlayerMovementStates/PlayerClimbingState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <ECS/Entity.hpp>

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

    return nullptr;
}