#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <string>

struct TimeComponent : public Component
{
    TimeComponent(int timeLeft) : timer(timeLeft) {}
    int timer = 0;
    float subtimer = 0;
    bool isPaused = false;
    bool goesFaster = false;
    bool firstTimeReach0 = false;
    bool firstTimePause = false;
    int timeUnitLeft = 0;
};

struct CoinComponent : public Component
{
    int coins = 0; // Initialize coins to 0
};

struct TextComponent : public Component
{
    TextComponent(std::string text, float startX, float startY, float finalY, float size, int seconds)
        : content(text), startX(startX), startY(startY), finalY(finalY), size(size)
    {
        dy = (startY - finalY) / seconds; // Calculate the vertical speed based on the total time
    }
    float startX = 0.0f;
    float startY = 0.0f;
    float finalY = 0.0f;
    float dy = 0.0f;
    float size = 0;
    std::string content;
};

struct LevelComponent : public Component
{
    LevelComponent(int level) : currentLevel(level) {}
    int currentLevel = 1; // Initialize currentLevel to 1
};

struct ThemeComponent : public Component
{
    ThemeComponent(int theme) : currentTheme(theme) {}
    int currentTheme = 1; // Initialize currentTheme to 0
};

// Just for score purpose
struct ShouldUpdateScore : public Component
{
    ShouldUpdateScore(int score) : score(score) {}
    int score;
};