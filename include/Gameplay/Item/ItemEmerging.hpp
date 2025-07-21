#pragma once
#include <ECS/Component.hpp>

struct ItemEmerging : public Component
{
    float finalY = 0.0f;
    float speedY = 40.0f;
    bool finished = false;
};