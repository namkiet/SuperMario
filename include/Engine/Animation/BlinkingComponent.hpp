#pragma once
#include <ECS/Component.hpp>

struct BlinkingComponent : public Component 
{
    BlinkingComponent(float interval = 0.0f, float duration = 0.0f) 
        : interval(interval)
        , duration(duration)
        , timer(0.0f)
        , visible(true) {}

    float interval;
    float duration;
    float timer;
    bool visible;
};