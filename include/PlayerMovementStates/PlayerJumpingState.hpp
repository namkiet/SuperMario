#pragma once
#include <PlayerMovementStates/PlayerMovementState.hpp>

class PlayerJumpingState : public PlayerMovementState
{
public:
    const std::string getName() const override;
    std::shared_ptr<PlayerMovementState> getNewState(Entity* entity) override;
};