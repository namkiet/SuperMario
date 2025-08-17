#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <string>

struct TextComponent : public Component
{
    TextComponent() = default;

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

// Just for score purpose
struct ShouldUpdateScore : public Component
{
    ShouldUpdateScore(int score) : score(score) {}
    int score;
};