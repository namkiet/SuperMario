#pragma once

#include <ECS/System.hpp>
#include <Framework/World.hpp>

#include <Engine/Core/DespawnTag.hpp>

#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Player/Components.hpp>

#include <LevelManager.hpp>

#include <TimeManager.hpp>

#include <World.hpp>

class PlayTimeSystem : public System
{
private:
    float timer = 0.0f;

public:
    void update(World &world, float dt)
    {
        timer += dt;
        if (timer > 1.0f || TimeManager::instance().getTimeGoesFaster())
        {
            TimeManager::instance().decrementTime();
            timer = 0;
        }
        else if (!TimeManager::instance().getTimeGoesFaster() && TimeManager::instance().getTime() <= 0)
        {
            Entity *player = world.findFirst<PlayerTag>();
            player->addComponent<DespawnTag>(); // Add a tag to despawn the entity
            LevelManager::instance().setStatus("timeup");
        }
    }
};