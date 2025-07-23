#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Prefabs/Mario.hpp>
#include <fstream>

class PlayerRespawnSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        std::ofstream fout("output.txt", std::ios::app);
        if (fout.fail())
        {
            std::cerr << "Failed to open output.txt for writing." << std::endl;
            return;
        }
        if (world.findFirst<PlayerTag>())
            return;
        // world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50);
        world.createEntity<Mario>(3 * 16, 12 * 16, 16, 16, 3);
        // fout << "Player respawned at position: (3*16, 12*16)" << std::endl;
        fout.close();
        // std::cout << "Player respawned!" << std::endl;
    }
};