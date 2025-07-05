#pragma once
#include <World.hpp>
#include <Components/DeadTag.hpp>
#include <Components/Health.hpp>
#include <Components/LifeSpan.hpp>

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
                entity->addComponent<DeadTag>();
            }
        }

        for (Entity* entity : world.findAll<Health>())
        {
            auto& hp = entity->getComponent<Health>().hp;
            if (hp == 0)
            {
                entity->addComponent<DeadTag>();
            }
        }
        
        for (Entity* entity : world.findAll<DeadTag>())
        {
            bool isPlayer = entity->hasComponent<PlayerTag>();
            world.destroyEntity(entity);
            if (isPlayer)
            {
                world.createEntity(std::make_unique<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 100)); 
            }
        }
    }
};