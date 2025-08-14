#pragma once
#include <ECS/Component.hpp>
#include <memory>

class PlayerMovementState;
class PlayerSizeState;
class PlayerPowerState;

struct PlayerTag : public Component 
{
    PlayerTag(std::shared_ptr<PlayerMovementState> movementState, std::shared_ptr<PlayerSizeState> sizeState, std::shared_ptr<PlayerPowerState> powerState, bool isMario = true) 
        : movementState(movementState), sizeState(sizeState), powerState(powerState) {}

    std::shared_ptr<PlayerMovementState> movementState;
    std::shared_ptr<PlayerSizeState> sizeState;
    std::shared_ptr<PlayerPowerState> powerState;
    bool isMario = true;
};

struct BigMarioTag : public Component {};
struct FireMarioTag : public Component {};
struct GrowUpTag : public Component{};

struct InputTag: public Component 
{
    int horizontalMovement = 0;
    bool jumpPressed = false;
};

struct InvincibleTag : public Component
{
    InvincibleTag(float duration) : duration(duration) {}
    float duration;
    float timer = 0.0f;
};