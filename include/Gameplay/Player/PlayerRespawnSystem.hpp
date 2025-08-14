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
        if (world.findFirst<PlayerTag>())
            return;

        auto mario = world.createEntity<Mario>((float)0 * 16, (float)6 * 16, 16, 16, 3);
        mario->addComponent<GrowUpTag>();
        mario->addComponent<FireMarioTag>();
    }
};