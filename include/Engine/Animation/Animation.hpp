#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <vector>

struct Animation : public Component
{
    Animation() = default;

    Animation(const sf::Texture& texture)
        : sprite(texture)
        , frameWidth(texture.getSize().x)
        , frameHeight(texture.getSize().y)
        , frameCount(1)
        , frameDuration(0)
        , loop(true) 
    {
        textures.push_back(&texture);
        update(0);
    }

    Animation(const sf::Texture &texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, bool loop = true)
        : sprite(texture)
        , frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(frameCount)
        , frameDuration(frameDuration)
        , loop(loop) 
        {
            textures.push_back(&texture);
            update(0);
        }

    Animation(std::vector<const sf::Texture*> textures, int frameWidth, int frameHeight, float frameDuration, bool loop) 
        : frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(textures.size())
        , frameDuration(frameDuration)
        , loop(loop)
        , textures(textures) 
        {
            update(0);
        }

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

    void update(float dt)
    {
        timer += dt;
        if (timer >= frameDuration)
        {
            timer -= frameDuration;
            currentFrame++;

            if (currentFrame >= frameCount)
            {
                if (loop)
                {
                    currentFrame = 0;
                }
                else
                {
                    currentFrame = frameCount - 1;
                    hasEnded = true;
                }
            }

        }

        if (textures.size() == 1)
        {
            sprite.setTexture(*textures[0]);
            sprite.setTextureRect(sf::IntRect(
                currentFrame * frameWidth,
                row * frameHeight,
                frameWidth,
                frameHeight
            ));
        }
        else
        {
            sprite.setTexture(*textures[currentFrame]);
        }
    }
};

struct FlipXTag : public Component {};
struct FlipYTag : public Component {};

inline void updateAnimation(Animation& anim, float dt)
{
    anim.timer += dt;
    if (anim.timer >= anim.frameDuration)
    {
        anim.timer -= anim.frameDuration;
        anim.currentFrame++;

        if (anim.currentFrame >= anim.frameCount)
        {
            if (anim.loop)
            {
                anim.currentFrame = 0;
            }
            else
            {
                anim.currentFrame = anim.frameCount - 1;
                anim.hasEnded = true;
            }
        }

    }

    if (anim.textures.size() == 1)
    {
        anim.sprite.setTexture(*anim.textures[0]);
        anim.sprite.setTextureRect(sf::IntRect(
            anim.currentFrame * anim.frameWidth,
            anim.row * anim.frameHeight,
            anim.frameWidth,
            anim.frameHeight
        ));
    }
    else
    {
        anim.sprite.setTexture(*anim.textures[anim.currentFrame]);
    }
}