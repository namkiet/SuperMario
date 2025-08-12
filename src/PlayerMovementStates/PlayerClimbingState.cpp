#include <PlayerMovementStates/PlayerClimbingState.hpp>
#include <PlayerMovementStates/PlayerRunningState.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerClimbingState::getName() const
{
    return "Climbing";
}

std::shared_ptr<PlayerMovementState> PlayerClimbingState::getNewState(Entity* entity)
{
    if (!entity->hasComponent<ClimbingOnFlagPoleTag>()) 
    {
        return std::make_shared<PlayerRunningState>();
    }

    return nullptr;
}