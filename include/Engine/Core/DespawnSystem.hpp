#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Audio/Components.hpp>
#include <Gameplay/Player/Components.hpp>

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

            if (deathTimer < 2.5f)
                return;

            deathTimer = 0.0f;
            world.destroyEntity(entity);
        }
    }
};
