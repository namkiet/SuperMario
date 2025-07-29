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
    TimeComponent(int timeLeft) : timer(timeLeft), dt(15) {}
    int timer = 0;
    int subtimer = 0;
    int dt = 0;
    bool isPaused = false;
    bool goesFaster = false;
    bool firstTimeReach0 = false;
    bool firstTimePause = false;
    int timeUnitLeft = 3;
};

struct CoinComponent : public Component
{
    int coins = 0; // Initialize coins to 0
};

struct TextComponent : public Component
{
    TextComponent(std::string text, float xPos, float yPos, float size, float dt, float dy)
        : content(text), x(xPos), y(yPos), size(size), dt(dt), dy(dy) {}
    float x = 0.0f;
    float y = 0.0f;
    float size = 0;
    std::string content;
    float timer = 0.0f; // Timer for how long the text should appear
    float dt = 0.0f;
    float dy = 0.0f; // Vertical movement speed
};
