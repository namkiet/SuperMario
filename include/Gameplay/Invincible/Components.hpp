#pragma once
#include <ECS/Component.hpp>

struct InvincibleTag : public Component
{
    InvincibleTag(float duration = 0.0f) : duration(duration) {}
    float duration;
    float timer = 0.0f;
};