#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <PlayerMovementStates/PlayerIdlingState.hpp>
#include <PlayerMovementStates/PlayerRunningState.hpp>
#include <PlayerMovementStates/PlayerJumpingState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerFireState.hpp>
#include <PlayerPowerStates/PlayerGrowingUpState.hpp>

inline void to_json(json& j, const std::shared_ptr<PlayerMovementState>& state)
{
    j = state ? state->getName() : "";
}

inline void from_json(const json& j, std::shared_ptr<PlayerMovementState>& state)
{
    state = nullptr;
    if (j.is_string() && !j.get<std::string>().empty())
    {
        std::string name = j.get<std::string>();

        if (name == "Idling") state = std::make_shared<PlayerIdlingState>();
        else if (name == "Jumping") state = std::make_shared<PlayerJumpingState>();
        else if (name == "Running") state = std::make_shared<PlayerRunningState>();
    }
}

inline void to_json(json& j, const std::shared_ptr<PlayerPowerState>& state)
{
    j = state ? state->getName() : "";
}

inline void from_json(const json& j, std::shared_ptr<PlayerPowerState>& state)
{
    state = nullptr;
    if (j.is_string() && !j.get<std::string>().empty())
    {
        std::string name = j.get<std::string>();

        if (name == "Small") state = std::make_shared<PlayerSmallState>();
        else if (name == "Big") state = std::make_shared<PlayerBigState>();
        else if (name == "Fire") state = std::make_shared<PlayerFireState>();
        else if (name == "GrowingUp") state = std::make_shared<PlayerGrowingUpState>();
    }
}

#include <Gameplay/Enemy/Goomba/GoombaNormalState.hpp>
#include <Gameplay/Enemy/Goomba/GoombaBehaviour.hpp>

inline void to_json(json& j, const std::shared_ptr<EnemyState>& state)
{
    j = "GoombaNormal";
}

inline void from_json(const json& j, std::shared_ptr<EnemyState>& state)
{
    state = std::make_shared<GoombaNormalState>();
}

inline void to_json(json& j, const std::shared_ptr<EnemyBehaviour>& state)
{
    j = "GoombaBehaviour";
}

inline void from_json(const json& j, std::shared_ptr<EnemyBehaviour>& state)
{
    state = std::make_shared<GoombaBehaviour>();
}
