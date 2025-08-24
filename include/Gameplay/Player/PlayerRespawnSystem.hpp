#pragma once

#include <ECS/System.hpp>
#include <GameManager.hpp>
#include <Framework/World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <LevelManager.hpp>

class PlayerRespawnSystem : public System
{
public:
    PlayerRespawnSystem(GameManager& gameMgr)
        : gameMgr(gameMgr) {}

    void update(World &world, float dt) override
    {
        if (world.findFirst<PlayerTag>())
            return;

        if (gameMgr.canEdit || gameMgr.currentLevel == -1)
        {
            gameMgr.init();
        }
        else
        {
            LevelManager::instance().setLevel(0);
            LevelManager::instance().setStatus("intro");
        }
        
    }
private:
    GameManager& gameMgr;
};
