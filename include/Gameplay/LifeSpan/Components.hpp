#pragma once
#include <ECS/Component.hpp>

struct LifeSpan : public Component
{
    LifeSpan(float value = 0.f) : value(value) {}
    float value;
};

struct Health : public Component
{
    Health(int hp = 0) : hp(hp) {}
    int hp;
};