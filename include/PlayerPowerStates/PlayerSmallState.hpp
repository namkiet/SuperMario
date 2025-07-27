#pragma once
#include <PlayerPowerStates/PlayerPowerState.hpp>

class PlayerSmallState : public PlayerPowerState
{
public:
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    std::shared_ptr<PlayerPowerState> getNewState(Entity* entity) override;
};