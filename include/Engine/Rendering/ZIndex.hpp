#pragma once
#include <ECS/Component.hpp>

struct ZIndex : public Component
{
    ZIndex(int value = 0) : value(value) {}
    int value = 0;
};