#pragma once
#include <ECS/Component.hpp>

class Gravity : public Component
{
public:
    Gravity(float g) : g(g) {}
    float g;
};