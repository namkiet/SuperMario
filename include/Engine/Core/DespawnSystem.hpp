#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Core/DespawnTag.hpp>

class DespawnSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<DespawnTag>())
        {
            world.destroyEntity(entity);
        }
    }
};
