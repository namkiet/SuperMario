#pragma once
#include <Gameplay/Player/PlayerMovementStates/PlayerMovementState.hpp>

class PlayerShootingState : public PlayerMovementState
{
public:
    PlayerShootingState();
    const std::string getName() const override;
    void update(Entity* entity, float dt) override;
    std::shared_ptr<PlayerMovementState> getNewState(Entity* entity) override;

private:
    float animationTimer;
};