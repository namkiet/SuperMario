#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Audio/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
class DespawnSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<DespawnTag>())
        {
            if (!entity->hasComponent<PlayerTag>()) world.destroyEntity(entity);
            
            // for player
            static float deathTimer = 0.0f;
            deathTimer += dt;

            if (deathTimer < 3.0f)
                return;

            deathTimer = 0.0f;
            world.destroyEntity(entity);
            // std::cout <<"num live left" << GameManager::getLives() << std::endl;
            if (GameManager::getLives() <= 1)
            {
                world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/gameover.wav"), false, true, sf::Time(sf::seconds(1000.f)));
                std::cout << "Create gameover sound ok" << std::endl;
            }
        }
    }
};
