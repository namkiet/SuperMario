#pragma once
#include <World.hpp>
#include <Components/Animation.hpp>
#include <Components/Sprite2D.hpp>
#include <SFML/Graphics.hpp>

class AnimationSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<Animation, Sprite2D>())
        {
            auto& anim = entity->getComponent<Animation>();
            auto& sp = entity->getComponent<Sprite2D>();

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
            sp.sprite.setTextureRect(sf::IntRect(
                anim.currentFrame * anim.frameWidth,
                anim.row * anim.frameHeight,
                anim.frameWidth,
                anim.frameHeight
            ));
        }
    }
};