#pragma once
#include <Gameplay/Player/PlayerSizeStates/PlayerSizeState.hpp>

class PlayerFireState : public PlayerSizeState
{
public:
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    void onExit(Entity* entity) override;
    std::shared_ptr<PlayerSizeState> getNewState(Entity* entity) override;
};