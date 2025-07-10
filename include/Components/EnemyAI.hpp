#pragma once
#include <ECS/Component.hpp>

struct EnemyAI : public Component
{
    float moveSpeed = 30.0f;
    bool isMovingRight = true;
};