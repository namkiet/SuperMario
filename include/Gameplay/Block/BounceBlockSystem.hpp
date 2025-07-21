#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Engine/Core/Transform.hpp>
#include <iostream>

class BounceBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *block : world.findAll<BounceBlock>())
        {
            auto &bounce = block->getComponent<BounceBlock>();
            auto &pos = block->getComponent<Transform>().position;

            bounce.timer += dt;

            if (bounce.timer >= bounce.bounceTime)
            {
                bounce.timer = 0.0f;
                pos.y = bounce.originalY;
                block->removeComponent<BounceBlock>();
            }
        }
    }
};