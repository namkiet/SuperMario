#pragma once
#include <ECS/Component.hpp>

struct CanCaptureFlagTag : public Component {};

struct SlidingOnFlagPoleTag : public Component {};

struct FlagPoleTag : public Component {};

struct HoldingTimer : public Component
{
    HoldingTimer(float duration) : duration(duration) {}
    float duration;
};