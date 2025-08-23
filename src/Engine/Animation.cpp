#include <Engine/Animation/Animation.hpp>

void Animation::update(float dt)
{
    if (textures.empty()) return;

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