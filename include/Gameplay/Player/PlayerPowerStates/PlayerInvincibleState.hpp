#pragma once
#include <Gameplay/Player/PlayerPowerStates/PlayerPowerState.hpp>

class PlayerInvincibleState : public PlayerPowerState
{
public:
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    void onExit(Entity* entity) override;
    void update(Entity* entity, float dt) override;
    std::shared_ptr<PlayerPowerState> getNewState(Entity* entity) override;
};