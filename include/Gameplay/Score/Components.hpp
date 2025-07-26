#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <string>

struct ScoreComponent : public Component
{
    int score = 0; // Initialize score to 0
};

struct TimeComponent : public Component
{
    int timer = 300;  // Initialize time to 300 seconds (5 minutes)
    int subtimer = 0; // Initialize sub-timer to 0
};

struct CoinComponent : public Component
{
    int coins = 0; // Initialize coins to 0
};

struct TextComponent : public Component
{
    float x = 0.0f;
    float y = 0.0f;
    float size = 20.0f;
    std::string content;
    float timer = 0.0f; // Timer for how long the text should appear
};

