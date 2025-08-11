#pragma once
#include <ECS/Component.hpp>

struct BlinkingComponent : public Component 
{
    BlinkingComponent(float interval = 0.0f) 
        : interval(interval), timer(0.0f), visible(true) {}

    float interval;
    float timer = 0.0f;
    bool visible = true;
};