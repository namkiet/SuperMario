#pragma once
#include <ECS/Component.hpp>
#include <memory>

class PlayerMovementState;
class PlayerPowerState;

struct PlayerTag : public Component 
{
    PlayerTag(std::shared_ptr<PlayerMovementState> movementState, std::shared_ptr<PlayerPowerState> powerState) 
        : movementState(movementState), powerState(powerState) {}

    std::shared_ptr<PlayerMovementState> movementState;
    std::shared_ptr<PlayerPowerState> powerState;
};

struct BigMarioTag : public Component {};
struct FireMarioTag : public Component {};
struct GrowUpTag : public Component{};

struct InputTag: public Component {};