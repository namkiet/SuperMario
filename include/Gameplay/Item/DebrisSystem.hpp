#pragma once
#include <World.hpp>
#include <Prefabs/Debris.hpp>
#include <Engine/Core/Transform.hpp>
#include <fstream>
class DebrisSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        std::ofstream fout("output.txt", std::ios::app);
        if (fout.fail())
        {
            cerr << "Failed to open output.txt for writing." << std::endl;
            return;
        }
        for (Entity *debris : world.findAll<DebrisTag, Transform>())
        {
            auto &pos = debris->getComponent<Transform>().position;
            auto &rb = debris->getComponent<RigidBody>();

            if (debris->hasComponent<Debris1Tag>())
            {
                pos.x -= 100 * dt;           // Move the debris to the left
                pos.y += rb.velocity.y * dt; // Move the debris upwards
                // fout << "Debris1Tag: Position updated to (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
            else if (debris->hasComponent<Debris2Tag>())
            {
                pos.x -= 100 * dt;               // Move the debris to the left
                pos.y += rb.velocity.y * dt - 2; // Move the debris upwards
                // fout << "Debris2Tag: Position updated to (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
            else if (debris->hasComponent<Debris3Tag>())
            {
                pos.x += 100 * dt;           // Move the debris to the left
                pos.y += rb.velocity.y * dt; // Move the debris upwards
                // fout << "Debris3Tag: Position updated to (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
            else if (debris->hasComponent<Debris4Tag>())
            {
                pos.x += 100 * dt;               // Move the debris to the left
                pos.y += rb.velocity.y * dt - 2; // Move the debris upwards
                // fout << "Debris4Tag: Position updated to (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
        }
        fout.close();
    }
};