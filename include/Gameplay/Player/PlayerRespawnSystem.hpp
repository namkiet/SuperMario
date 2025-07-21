#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Prefabs/Mario.hpp>

class PlayerRespawnSystem : public System 
{
public:
    void update(World& world, float dt) override 
    {
        if (world.findFirst<PlayerTag>()) return;
        // world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50);
        world.createEntity<Mario>(3*16, 12*16, 16, 16, 3);
        // std::cout << "Player respawned!" << std::endl;
    }
};