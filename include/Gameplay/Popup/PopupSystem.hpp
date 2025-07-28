#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Popup/Components.hpp>

class PopupSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        for (Entity* entity : world.findAll<PopupComponent, RigidBody>())
        {
            auto& popup = entity->getComponent<PopupComponent>();
            auto& rb = entity->getComponent<RigidBody>();
            rb.velocity.y = popup.speed * (popup.goingUp ? -1 : 1);
            popup.timer += dt;
            if (popup.timer >= popup.delay)
            {
                popup.timer = 0.0f;
                popup.goingUp = !popup.goingUp;
            }
        }
    }
};