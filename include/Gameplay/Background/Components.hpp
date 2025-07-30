#pragma once
#include <ECS/Component.hpp>

struct Castle : public Component
{
    // This component can be used to tag entities that represent a castle background
};

struct FlagPole : public Component
{
    // This component can be used to tag entities that represent a flagpole background
};

struct Flag : public Component
{
    // This component can be used to tag entities that represent a flag background
};

struct CastleFlag : public Component
{
    // This component can be used to tag entities that represent a castle flag background
};
