#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Gameplay/LifeSpan/Components.hpp>

class LifeSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<LifeSpan>())
        {
            auto& ls = entity->getComponent<LifeSpan>();
            ls.value -= dt;
            if (ls.value <= 0.0f)
            {
                entity->addComponent<DespawnTag>();
            }
        }
    }
};