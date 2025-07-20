#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Prefabs/Mario.hpp>
#include <math.h>

class ResetSystem : public System
{
    public:
    void update(World& world, float dt) override
    {
        auto player = world.findFirst<PlayerTag>();
        if (!player) return;

        auto& rigid = player->getComponent<RigidBody>();

        rigid.velocity.x = 0;
        
        if (rigid.onGround)
        {
            rigid.velocity.y = std::min(rigid.velocity.y, 0.0f);
            std::cout << "Still on the ground" << std::endl;
        }

        std::cout << "at the end of reset system, velocity: " 
                  << rigid.velocity.x << ", " << rigid.velocity.y << std::endl;
    }
};