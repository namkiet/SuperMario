#pragma once
#include <ECS/Component.hpp>

struct CanCaptureFlagTag : public Component {};

struct ClimbingOnFlagPoleTag : public Component {};

struct FlagPoleTag : public Component {};

struct HoldingTimer : public Component
{
    HoldingTimer(float duration = 0.0f) : duration(duration) {}
    float duration;
};