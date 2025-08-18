#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
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
            auto &rb = block->getComponent<RigidBody>();

            block->addComponent<CanKillEnemyTag>();

            float futureY = pos.y + (rb.velocity.y + PHYSICS::GRAVITY * dt) * dt;

            if (abs(bounce.originalY - pos.y) < abs(bounce.originalY - futureY) && rb.velocity.y > 0)
            {
                pos.y = bounce.originalY;
                block->removeComponent<CanKillEnemyTag>();
                block->removeComponent<BounceBlock>();
                block->removeComponent<RigidBody>();
            }
        }
        // fout.close();
    }
};