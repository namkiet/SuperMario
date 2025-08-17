#pragma once
#include <Framework/World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Gameplay/Player/Components.hpp>

#include <LevelManager.hpp>

#include <World.hpp>

class CollectMushroomSystem : public System
{
    void update(World &world, float dt) override
    {
        bool shouldReloadLevel = false; // Reset at start of update
        int newLevel = 1;
        for (Entity *player : world.findAll<CanCollectTag, PlayerTag, BoxCollider2D>())
        {
            for (const auto &[item, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the entity can collect the item
                if (!item->hasComponent<CollectableTag>())
                    continue;
                if (!item->hasComponent<MushroomTag>())
                    continue;

                if (!player->hasComponent<BigMarioTag>())
                {
                    player->addComponent<GrowUpTag>();
                }

                auto &mushroomTag = item->getComponent<MushroomTag>();
                if (mushroomTag.buff == MushroomTag::Buff::GIVE_ONE_MORE_LIFE)
                {
                    world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/1up.wav"));
                }
                else if (mushroomTag.buff == MushroomTag::Buff::GET_TO_LEVEL_1)
                {
                    newLevel = 1;
                    shouldReloadLevel = true;
                    // std::cout << "Collect Mushroom: GET_TO_LEVEL_1\n";
                }
                else if (mushroomTag.buff == MushroomTag::Buff::GET_TO_LEVEL_2)
                {
                    newLevel = 2;
                    shouldReloadLevel = true;
                    // std::cout << "Collect Mushroom: GET_TO_LEVEL_2\n";
                }
                else if (mushroomTag.buff == MushroomTag::Buff::GET_TO_LEVEL_3)
                {
                    newLevel = 3;
                    shouldReloadLevel = true;
                    // std::cout << "Collect Mushroom: GET_TO_LEVEL_3\n";
                }
            }
        }
        if (shouldReloadLevel)
        {
            LevelManager::instance().setLevel(newLevel);
            LevelManager::instance().setStatus("intro");
        }
    }
};