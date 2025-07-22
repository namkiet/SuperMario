#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <string>
#include <unordered_map>

struct Animation : public Component
{
    Animation() = default;

    Animation(const sf::Texture& texture)
        : sprite(texture)
        , frameWidth(texture.getSize().x)
        , frameHeight(texture.getSize().y)
        , frameCount(1)
        , frameDuration(0)
        , loop(true) {}

    Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true)
        : sprite(texture)
        , frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(frameCount)
        , frameDuration(frameDuration)
        , loop(loop) {}

    sf::Sprite sprite;
    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration; 
    int currentFrame = 0;
    float timer = 0.f;
    bool loop = true;
    int row = 0; 
    bool flipX = false;
    bool flipY = false;
    bool hasEnded = false;

// private:
//     std::unordered_map<std::string, 
};