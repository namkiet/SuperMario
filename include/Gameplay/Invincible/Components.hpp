#pragma once
#include <ECS/Component.hpp>

struct InvincibleTag : public Component
{
    InvincibleTag(float duration) : duration(duration) {}
    float duration;
    float timer = 0.0f;
};