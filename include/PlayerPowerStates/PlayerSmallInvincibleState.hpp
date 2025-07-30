#pragma once
#include <PlayerPowerStates/PlayerPowerState.hpp>

class PlayerSmallInvincibleState : public PlayerPowerState
{
public:
    const std::string getName() const override;
    std::shared_ptr<PlayerPowerState> getNewState(Entity* entity) override;
};