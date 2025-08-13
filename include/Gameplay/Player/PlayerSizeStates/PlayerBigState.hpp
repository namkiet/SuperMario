#pragma once
#include <Gameplay/Player/PlayerSizeStates/PlayerSizeState.hpp>

class PlayerBigState : public PlayerSizeState
{
public:
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    std::shared_ptr<PlayerSizeState> getNewState(Entity* entity) override;
};