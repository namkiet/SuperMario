#pragma once
#include <Gameplay/Player/PlayerSizeStates/PlayerSizeState.hpp>

class PlayerShrinkingState : public PlayerSizeState
{
public:
    PlayerShrinkingState();
    const std::string getName() const override;
    void onEnter(Entity* entity) override;
    void onExit(Entity* entity) override;
    void update(Entity* entity, float dt) override;
    std::shared_ptr<PlayerSizeState> getNewState(Entity* entity) override;

private:
    float animationDuration;
    float animationTimer;
};