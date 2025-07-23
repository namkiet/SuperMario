#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/HitBlock/Components.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/Item/ItemEmerging.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Flower.hpp>
#include <Prefabs/Mushroom.hpp>

class HitQuestionBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<BoxCollider2D, CanHitQuestionBlockTag>())
        {
            for (auto &[block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<QuestionBlockTag>())
                    continue;
                if (direction != Direction::Bottom)
                    continue;

                block->removeComponent<QuestionBlockTag>();

                // Change texture of the block after hit
                if (block->hasComponent<Animation>())
                {
                    block->removeComponent<Animation>();
                    block->addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_27.png"));
                }

                // Spawn a coin entity on top of it
                if (block->hasComponent<Transform>())
                {
                    auto &tf = block->getComponent<Transform>();
                    auto &pos = tf.position;
                    auto &sz = tf.size;

                    if (block->hasComponent<FlowerQuestionBlock>())
                    {
                        auto flower = world.createEntity<Flower>(pos.x, pos.y - sz.y, 48, 48);
                        flower->addComponent<CollectableTag>();
                    }
                    else if (block->hasComponent<MushroomQuestionBlock>())
                    {
                        auto mushroom = world.createEntity<Mushroom1>(pos.x, pos.y, 48, 48);
                        ItemEmerging emerging;
                        // cout << pos.y << endl;
                        emerging.finalY = pos.y - 48;
                        mushroom->addComponent<ItemEmerging>(emerging);
                    }
                    else if (block->hasComponent<CoinQuestionBlock>())
                    {
                        world.createEntity<Coin1>(pos.x, pos.y - sz.y, 48, 48);
                    }

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
