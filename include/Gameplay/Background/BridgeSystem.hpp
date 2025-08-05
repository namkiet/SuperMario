#pragma once
#include <World.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

#include <Gameplay/Background/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>

#include <iostream>

class BridgeSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D>())
        {
            for (const auto &[collider, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (!collider->hasComponent<BellTag>())
                    continue;

                // Get all bridge tiles
                auto bridgeTiles = world.findAll<BridgeTileTag, Transform>();
                // Optional: sort by index or position if needed
                std::vector<Entity *> sortedTiles(bridgeTiles.begin(), bridgeTiles.end());
                std::sort(sortedTiles.begin(), sortedTiles.end(), [](Entity *a, Entity *b)
                          { return a->getComponent<Transform>().position.x > b->getComponent<Transform>().position.x; });

                // Assign LifeSpanComponent with increasing delay
                float delay = 0.0f;
                float step = 0.1f; // seconds between each tile disappearing
                for (Entity *tile : sortedTiles)
                {
                    tile->addComponent<LifeSpan>(delay);
                    delay += step;
                }

                player->addComponent<RigidBody>(sf::Vector2f(200, 0));
                player->removeComponent<InputTag>();

                collider->removeComponent<BellTag>(); // Remove the BellTag after processing

                // If the fakebowser was defeated, keep the bridge
                // Else destroy the bridge and lock the player will the bridge tiles can still be seen
            }
        }
    }
};