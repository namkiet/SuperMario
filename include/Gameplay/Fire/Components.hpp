#pragma once
#include <ECS/Component.hpp>

struct CanFireTag: public Component
{
    // This tag is used to identify entities that can fire
};

struct FireCooldown : public Component
{
    float timeCount = 0.0f; // Time until the next fire can occur
};