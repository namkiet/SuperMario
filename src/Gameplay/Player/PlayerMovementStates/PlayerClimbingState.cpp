#include <Gameplay/Player/PlayerMovementStates/PlayerClimbingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerRunningState.hpp>
#include <Gameplay/CaptureFlag/Components.hpp>
#include <Entity/Entity.hpp>

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