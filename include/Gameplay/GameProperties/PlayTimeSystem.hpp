#pragma once

#include <ECS/System.hpp>
#include <Framework/World.hpp>

#include <Engine/Core/DespawnTag.hpp>

#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Player/Components.hpp>

#include <LevelManager.hpp>

#include <TimeManager.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <LevelManager.hpp>

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
            if (player) player->addComponent<DespawnTag>();                          // Add a tag to despawn the entity
            // else return;
            // static float timeUpTimer = 0.0f;
            // timeUpTimer += dt;
            // if (timeUpTimer >= 3.0f)
            // {
            //     LevelManager::instance().setStatus("timeup");
            //     LevelManager::instance().setPrevMarioPosition(player->getComponent<Transform>().position);
            //     // world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/gameover.wav"), false, true, sf::seconds(1000.f));
            //     // std::cout << "It looks good '================" << std::endl;
            //     timeUpTimer = 0.0f; // Reset timer for next time
            // }
        }
    }
};