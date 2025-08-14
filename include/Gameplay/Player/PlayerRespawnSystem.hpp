#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
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

        Entity *gameSession = world.findFirst<LevelComponent>();
        if (!gameSession)
            return;
        auto &levelComponent = gameSession->getComponent<LevelComponent>();
        
        world.setNewLevel(levelComponent.currentLevel);
        world.setStatus("intro");       
    }
};