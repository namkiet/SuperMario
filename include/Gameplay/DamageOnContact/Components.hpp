#pragma once
#include <ECS/Component.hpp>
#include <vector>

enum class Direction;

struct CanGetDamageTag : public Component {};

struct DamageOnContactComponent : public Component 
{   
    DamageOnContactComponent(const std::vector<Direction>& validDirections = {})
        : validDirections(validDirections) {}
    std::vector<Direction> validDirections;
};

struct DamagedTag : public Component {};