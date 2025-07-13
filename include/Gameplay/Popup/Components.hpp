#pragma once
#include <ECS/Component.hpp>

struct PopupComponent :  public Component
{
    PopupComponent(float height, float delay)
        : speed(height / delay) , delay(delay) {}

    float timer = 0.0f;
    bool goingUp = true;

    float delay;
    float speed;
};