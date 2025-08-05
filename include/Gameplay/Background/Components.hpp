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
    // This component can be used to tag entities that represent a bell in the background
};

struct BridgeTileTag : public Component
{
    // This component can be used to tag entities that represent a bridge tile in the background
};

struct ElevatorComponent : public Component
{
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };
    ElevatorComponent(float currentX, float finalX, int dir)
    {
        direction = static_cast<Direction>(dir - 1);
        if (direction == Direction::Right)
        {
            minimumX = currentX;
            maximumX = finalX;
        }
        else if (direction == Direction::Left)
        {
            minimumX = finalX;
            maximumX = currentX;
        }
    }
    Direction direction;
    Animation animation;
    float maximumX = 0;
    float minimumX = 0;
};

struct Princess : public Component
{
    // This component can be used to tag entities that represent a princess in the background
};