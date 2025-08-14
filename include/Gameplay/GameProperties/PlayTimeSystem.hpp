#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/DespawnTag.hpp>

class PlayTimeSystem : public System
{
    void update(World &world, float dt)
    {
        for (Entity *entity : world.findAll<TimeComponent>())
        {
            TimeComponent &timeComponent = entity->getComponent<TimeComponent>();
            if (timeComponent.timer > 0)
            {
                timeComponent.subtimer += dt;
                if (timeComponent.subtimer >= 1.0f && !timeComponent.isPaused) // Increment timer every second
                {
                    --timeComponent.timer;
                    timeComponent.subtimer = 0.0f; // Reset sub-timer
                }
                else if (timeComponent.goesFaster)
                {
                    --timeComponent.timer;
                }
            }
            else if (timeComponent.timer <= 0 && !timeComponent.goesFaster)
            {
                timeComponent.timer = 0; // Ensure it doesn't go negative
                Entity *player = world.findFirst<PlayerTag>();
                player->addComponent<DespawnTag>(); // Add a tag to despawn the entity
                world.setStatus("timeup");
            }
            else if (timeComponent.timer <= 0 && timeComponent.goesFaster)
            {
                // If the timer is already at 0 and goesFaster is true, we can reset it or handle it as needed
                timeComponent.timer = 0; // Reset to 0 if needed
            }
        }
    }
};