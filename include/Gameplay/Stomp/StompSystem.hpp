#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Stomp/Components.hpp>

class StompSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        for (Entity* stomper : world.findAll<StomperTag, BoxCollider2D>())
        {
            for (auto& [stompable, direction] : stomper->getComponent<BoxCollider2D>().collisions)
            {
                if (!stompable->hasComponent<StompableTag>()) continue;
                
                if (direction == Direction::Top)
                {
                    stomper->getComponent<RigidBody>().velocity.y = -1000.0f;
                }
            }
        }
    }
};
