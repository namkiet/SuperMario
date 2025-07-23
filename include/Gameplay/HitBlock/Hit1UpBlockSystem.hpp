#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/HitBlock/Components.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/TextureManager.hpp>
#include <Prefabs/Mushroom.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Gameplay/Block/BounceBlock.hpp>

class Hit1UpBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<BoxCollider2D, CanHit1UpBlockTag>())
        {
            for (auto &[block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<LevelUpBlock>())
                    continue;
                if (direction != Direction::Bottom)
                    continue;

                block->removeComponent<LevelUpBlock>();

                // Change texture of the block after hit
                block->addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_27.png"));

                // Spawn a 1-Up Mushroom entity on top of it
                if (block->hasComponent<Transform>())
                {
                    auto &tf = block->getComponent<Transform>();
                    auto &pos = tf.position;
                    auto &sz = tf.size;

                    auto mushroom = world.createEntity<Mushroom2>(pos.x, pos.y, 48, 48);
                    ItemEmerging emerging;
                    // cout << pos.y << endl;
                    emerging.finalY = pos.y - 48;
                    mushroom->addComponent<ItemEmerging>(emerging);

                    // Bounce the block
                    if (!block->hasComponent<BounceBlock>())
                    {
                        BounceBlock bounce;
                        bounce.originalY = pos.y;
                        bounce.updateY = pos.y - (sz.y / 4);
                        block->addComponent<BounceBlock>(bounce);
                        pos.y = bounce.updateY;
                        // cout << "In HitQuestionBlockSystem, bouncing block at position: " << pos.x << ", " << pos.y << endl;
                    }
                }
            }
        }
    }
};