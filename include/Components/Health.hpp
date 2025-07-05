#pragma once
#include <ECS/Component.hpp>

struct Health : public Component
{
    Health(int hp) : hp(hp) {}
    int hp;
};