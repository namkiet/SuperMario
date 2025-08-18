#pragma once

#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <LevelManager.hpp>
#include <Prefabs/Mario.hpp>

class PlayerRespawnSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        if (world.findFirst<PlayerTag>())
            return;

        auto mario = world.createEntity<Mario>((float)0 * 16, (float)6 * 16, 16.0f, 16.0f, 3.0f);
        mario->addComponent<GrowUpTag>();
        mario->addComponent<CanFireTag>();
        
        LevelManager::instance().setLevel(0);
        LevelManager::instance().setStatus("intro");
    }
};