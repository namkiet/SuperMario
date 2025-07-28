#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/BreakBrick/Components.hpp>
#include <Prefabs/Coin.hpp>

class BreakBrickSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        for (Entity* entity : world.findAll<BoxCollider2D, CanBreakBrickTag>())
        {
            for (auto& [brick, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!brick->hasComponent<BrickTag>()) continue;
                if (direction != Direction::Bottom) continue;
                
                brick->addComponent<DespawnTag>();
            }
        }
    }
};
