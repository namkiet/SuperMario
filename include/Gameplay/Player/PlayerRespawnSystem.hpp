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
        world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50);
        std::cout << "Player respawned!" << std::endl;
    }
};