#pragma once
#include <ECS/Component.hpp>

struct BounceBlock : public Component
{
    float bounceTime = 0.3f;
    float timer = 0.0f;
    float updateY = 0.0f;
    float originalY = 0.0f;
};