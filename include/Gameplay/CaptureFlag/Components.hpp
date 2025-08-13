#pragma once
#include <ECS/Component.hpp>

struct CanCaptureFlagTag : public Component {};

struct ClimbingOnFlagPoleTag : public Component {};

struct FlagPoleTag : public Component {};

struct HoldingTimer : public Component
{
    HoldingTimer(float duration) : duration(duration) {}
    float duration;
};