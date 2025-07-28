#pragma once
#include <ECS/Component.hpp>

struct CollectableTag : public Component
{
    // Base class for collectable items
};

struct CanCollectTag : public Component
{
    // Base class for entities that can collect items
};