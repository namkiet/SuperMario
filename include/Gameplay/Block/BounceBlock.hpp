#pragma once
#include <ECS/Component.hpp>

struct BounceBlockTag : public Component
{
    float originalY = 0.0f;
    float bounceVel = -300;
};