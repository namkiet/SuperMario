#pragma once
#include <ECS/Component.hpp>

class Input : public Component
{
public:
    Input() = default;
    bool moveLeft = false;
    bool moveRight = false;
    bool jumpPressed = false;
    bool shootPressed = false;
};