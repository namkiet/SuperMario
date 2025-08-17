#pragma once
#include <ECS/Component.hpp>
#include <Engine/Animation/Animation.hpp>

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

struct BellTag : public Component
{
    bool firstHit = false;
    bool secondHit = false;
    // This component can be used to tag entities that represent a bell in the background
};

struct BridgeTileTag : public Component
{
    // This component can be used to tag entities that represent a bridge tile in the background
};

struct ElevatorComponent : public Component
{
    ElevatorComponent() = default;

    ElevatorComponent(float _min, float _max, bool isHorizontal) : isHorizontal(isHorizontal)
    {
        if (_min >= _max)
            std::swap(_min, _max);

        if (isHorizontal)
        {
            minX = _min;
            maxX = _max;
            minY = -100000.0;
            maxY = 100000.0;
        }
        else
        {
            minY = _min;
            maxY = _max;
            minX = -100000.0;
            maxX = 100000.0;
        }
    }

    bool isHorizontal;
    float minX;
    float maxX;
    float minY;
    float maxY;
};

struct Princess : public Component
{
    // This component can be used to tag entities that represent a princess in the background
};