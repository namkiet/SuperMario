#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <vector>

struct Animation : public Component
{
    Animation() = default;

    Animation(const sf::Texture& texture)
        : frameWidth(texture.getSize().x)
        , frameHeight(texture.getSize().y)
        , frameCount(1)
        , frameDuration(0)
        , loop(true) 
    {
        textures.push_back(&texture);
    }

    Animation(const sf::Texture &texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true)
        : frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(frameCount)
        , frameDuration(frameDuration)
        , loop(loop) 
        {
            textures.push_back(&texture);
        }

    Animation(std::vector<const sf::Texture*> textures, int frameWidth, int frameHeight, float frameDuration, bool loop) 
        : frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(textures.size())
        , frameDuration(frameDuration)
        , loop(loop)
        , textures(textures) {}

    sf::Sprite sprite;
    int frameWidth;
    int frameHeight;
    int frameCount;
    float frameDuration;
    int currentFrame = 0;
    float timer = 0.f;
    bool loop = true;
    int row = 0;
    bool hasEnded = false;
    std::vector<const sf::Texture *> textures;
};

struct FlipXTag : public Component {};
struct FlipYTag : public Component {};