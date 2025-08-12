#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Engine/Core/Transform.hpp>
#include <iostream>
#include <fstream>
class BounceBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        // std::ofstream fout("output.txt", std::ios::app);
        // if (fout.fail())
        // {
        //     std::cerr << "Failed to open output.txt for writing." << std::endl;
        //     return;
        // }
        for (Entity *block : world.findAll<BounceBlock>())
        {
            auto &bounce = block->getComponent<BounceBlock>();
            auto &pos = block->getComponent<Transform>().position;

            bounce.timer += dt;
            // fout << "Timer for bounce block" << std::endl;
            if (bounce.timer >= bounce.bounceTime)
            {
                bounce.timer = 0.0f;
                pos.y = bounce.originalY;
                block->removeComponent<BounceBlock>();
            }
        }
        // fout.close();
    }
};