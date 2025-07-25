#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>

struct ScoreComponent : public Component
{
    int score = 0; // Initialize score to 0
};