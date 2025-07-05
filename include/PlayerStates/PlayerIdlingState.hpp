#pragma once
#include <PlayerStates/PlayerState.hpp>

class PlayerIdlingState : public PlayerState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<PlayerState> getNewState(Entity* entity) override;
};