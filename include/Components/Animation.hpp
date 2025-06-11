#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

class Animation : public Component
{
public:
    Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true)
        : frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(frameCount)
        , frameDuration(frameDuration)
        , loop(loop) {}

    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration; 
    int currentFrame = 0;
    float timer = 0.f;
    bool loop = true;
    int row = 0; 
};