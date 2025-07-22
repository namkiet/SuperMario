#pragma once
#include <ECS/Component.hpp>
#include <PlayerMovementStates/PlayerMovementState.hpp>
#include <PlayerMovementStates/PlayerIdlingState.hpp>
#include <PlayerMovementStates/PlayerRunningState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <memory>

struct PlayerTag : public Component 
{
    PlayerTag(std::shared_ptr<PlayerMovementState> movementState, std::shared_ptr<PlayerPowerState> powerState) 
        : movementState(movementState), powerState(powerState) {}

    std::shared_ptr<PlayerMovementState> movementState;
    std::shared_ptr<PlayerPowerState> powerState;
};

struct BigTag : public Component {};
struct GrowUpTag : public Component{};