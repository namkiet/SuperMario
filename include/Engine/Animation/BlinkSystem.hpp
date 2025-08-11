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

            if (blink.timer >= blink.interval) 
            {
                blink.visible = !blink.visible;
                blink.timer = 0.f;

                sf::Color currentColor = anim.sprite.getColor();
                currentColor.a = blink.visible ? 255 : 0;
                anim.sprite.setColor(currentColor);
            }
        }
    }
};