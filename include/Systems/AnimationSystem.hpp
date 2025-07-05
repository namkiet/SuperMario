#pragma once
#include <World.hpp>
#include <Components/Animation.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimationSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Animation>())
        {
            auto& anim = entity->getComponent<Animation>();

            if (anim.frameCount == 1) continue;

            anim.timer += dt;
            if (anim.timer >= anim.frameDuration) 
            {
                anim.timer -= anim.frameDuration;
                anim.currentFrame++;

                if (anim.currentFrame >= anim.frameCount) 
                {
                    anim.currentFrame = anim.loop ? 0 : anim.frameCount - 1;
                }

            }

            // Set texture rect
            anim.sprite.setTextureRect(sf::IntRect(
                anim.currentFrame * anim.frameWidth,
                anim.row * anim.frameHeight,
                anim.frameWidth,
                anim.frameHeight
            ));
        }
    }
};