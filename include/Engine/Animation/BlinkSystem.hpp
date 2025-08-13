#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Animation/BlinkingComponent.hpp>
#include <Engine/Animation/Animation.hpp>
#include <SFML/Graphics.hpp>

class BlinkSystem : public System 
{
public:
    void update(World &world, float dt) override 
    {
        for (Entity* entity : world.findAll<BlinkingComponent, Animation>()) 
        {
            auto &blink = entity->getComponent<BlinkingComponent>();
            auto &anim = entity->getComponent<Animation>();

            blink.timer += dt;
            blink.duration -= dt;

            if (blink.timer >= blink.interval) 
            {
                blink.timer = 0.0f;
                blink.visible = !blink.visible;

                sf::Color currentColor = anim.sprite.getColor();
                currentColor.a = blink.visible ? 255 : 0;
                anim.sprite.setColor(currentColor);
            }

            if (blink.duration < 0.0f)
            {
                sf::Color currentColor = anim.sprite.getColor();
                currentColor.a = 255;
                anim.sprite.setColor(currentColor);
                entity->removeComponent<BlinkingComponent>();
            }
        }
    }
};