#pragma one
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Score/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
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
               ++timeComponent.subtimer;
               if (timeComponent.subtimer >= 30) // Increment timer every 60 frames
               {
                   timeComponent.timer--;
                   timeComponent.subtimer = 0; // Reset sub-timer
               }
            }
            else
            {
                timeComponent.timer = 0; // Ensure it doesn't go negative
                entity->addComponent<DespawnTag>(); // Add a tag to despawn the entity
            }
        }
    }
};