#pragma once
#include <ECS/Component.hpp>

struct PodobooTag : public Component
{
    PodobooTag(bool upright = true)
        : upright(upright)
    {
    }
    bool upright = true;
    float lowestY = 820.0f;
    float highestY = 240.0f;
};

struct FireBarComponent : public Component
{
    FireBarComponent(bool clockwise = true)
        : isClockwise(clockwise)
    {
    }
    float angle = 0.0f; // rotation angle for the bar
    bool isClockwise = true; // direction of rotation
};