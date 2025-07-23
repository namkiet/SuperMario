#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Hitblock/Components.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/TextureManager.hpp>
#include <Prefabs/Star.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Gameplay/Block/BounceBlock.hpp>

class HitStarBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<BoxCollider2D, CanHitStarBlockTag>())
        {
            for (auto &[block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<StarBlock>())
                    continue;
                if (direction != Direction::Bottom)
                    continue;

                block->removeComponent<StarBlock>();

                // Change texture of the block after hit
                block->addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_27.png"));

                // S
                if (block->hasComponent<Transform>())
                {
                    auto &tf = block->getComponent<Transform>();
                    auto &pos = tf.position;
                    auto &sz = tf.size;

                    auto star = world.createEntity<Star>(pos.x, pos.y, 48, 48);
                    ItemEmerging emerging;
                    // cout << pos.y << endl;
                    emerging.finalY = pos.y - 48;
                    star->addComponent<ItemEmerging>(emerging);

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