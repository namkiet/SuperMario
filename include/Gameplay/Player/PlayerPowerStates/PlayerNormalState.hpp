#pragma once
#include <Gameplay/Player/PlayerPowerStates/PlayerPowerState.hpp>

class PlayerNormalState : public PlayerPowerState
{
public:
    const std::string getName() const override;
    std::shared_ptr<PlayerPowerState> getNewState(Entity* entity) override;
};