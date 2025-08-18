#pragma once
#include <ECS/Component.hpp>

struct BounceBlock : public Component
{
    float originalY = 0.0f;
    float bounceVel = -300;
};