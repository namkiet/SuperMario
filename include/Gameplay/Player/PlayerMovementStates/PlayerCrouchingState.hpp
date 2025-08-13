#pragma once
#include <Gameplay/Player/PlayerMovementStates/PlayerMovementState.hpp>

class PlayerCrouchingState : public PlayerMovementState
{
public:
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    void onExit(Entity* entity) override;
    std::shared_ptr<PlayerMovementState> getNewState(Entity* entity) override;
};