#pragma once
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>

#include <Gameplay/Collect/Components.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Gameplay/Player/Components.hpp>

#include <World.hpp>

class CollectFlowerSystem : public System
{
    void update(World &world, float dt) override
    {
        for (Entity* player : world.findAll<CanCollectTag, PlayerTag, BoxCollider2D>())
        {
            for (const auto &[item, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                // Check if the entity can collect the item
                if (!item->hasComponent<CollectableTag>()) continue;
                if (!item->hasComponent<FlowerTag>()) continue;

                world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/powerup_collect.wav"));
                if (player->hasComponent<BigMarioTag>())
                {
                    player->addComponent<FireMarioTag>();
                }
                else
                {
                    player->addComponent<GrowUpTag>();
                }
            }
        }
    }
};