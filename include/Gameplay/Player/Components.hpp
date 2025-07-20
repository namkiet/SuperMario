#pragma once
#include <ECS/Component.hpp>
#include <PlayerStates/PlayerState.hpp>
#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <memory>

struct PlayerTag : public Component 
{
    PlayerTag(std::shared_ptr<PlayerState> state) : state(state) {}
    std::shared_ptr<PlayerState> state;
};

struct InputTag: public Component
{
};