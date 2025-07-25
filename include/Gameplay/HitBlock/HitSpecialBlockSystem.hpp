#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Core/TextureManager.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Player/Components.hpp>

class HitSpecialBlockSystem : public System
{
private:
    void Hit1UpBlock(World &world, float dt, Entity *block);
    void HitQuestionBlock(World &world, float dt, Entity *block);
    void HitCoinBlock(World &world, float dt, Entity *block);
    void HitNormalBlock(World &world, float dt, Entity *block); // Only for large mario
    void HitStarBlock(World &world, float dt, Entity *block);
    void CoinBlockUpdate(World &world, float dt, Entity *block);

public:
    void update(World &world, float dt) override
    {
        for (Entity *block : world.findAll<CoinBlock, CoinBlockComponent>())
        {
            CoinBlockUpdate(world, dt, block);
        }
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D>())
        {
            for (auto &[block, direction] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (direction != Direction::Bottom)
                    continue;

                if (!block->hasComponent<NormalBlock>() && !block->hasComponent<QuestionBlockTag>() &&
                    !block->hasComponent<CoinBlock>() && !block->hasComponent<StarBlock>() &&
                    !block->hasComponent<LevelUpBlock>())
                    continue;

                // Normal Block
                if (block->hasComponent<NormalBlock>() && player->hasComponent<BigMarioTag>())
                {
                    // Remove NormalBlock component
                    block->removeComponent<NormalBlock>();

                    // Add DespawnTag component
                    block->addComponent<DespawnTag>();

                    // Update
                    HitNormalBlock(world, dt, block);
                }
                else
                {
                    // Change texture of the block after hit
                    if (block->hasComponent<Animation>())
                    {
                        if (!block->hasComponent<NormalBlock>() && !block->hasComponent<CoinBlock>())
                            block->removeComponent<Animation>();
                    }
                    if (!block->hasComponent<NormalBlock>() && !block->hasComponent<CoinBlock>())
                        block->addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_27.png"));

                    if (block->hasComponent<LevelUpBlock>())
                    {
                        // Remove LevelUpBlock component
                        block->removeComponent<LevelUpBlock>();

                        // Update
                        Hit1UpBlock(world, dt, block);
                    }
                    else if (block->hasComponent<QuestionBlockTag>())
                    {
                        // Remove QuestionBlockTag component
                        block->removeComponent<QuestionBlockTag>();

                        // Update
                        HitQuestionBlock(world, dt, block);
                    }
                    else if (block->hasComponent<CoinBlock>())
                    {
                        // Remove CoinBlock component
                        // block->removeComponent<CoinBlock>();

                        // Update
                        HitCoinBlock(world, dt, block);
                    }
                    else if (block->hasComponent<StarBlock>())
                    {
                        // Remove StarBlock component
                        block->removeComponent<StarBlock>();

                        // Update
                        HitStarBlock(world, dt, block);
                    }

                    if (block->hasComponent<Transform>() && !block->hasComponent<BounceBlock>())
                    {
                        auto &tf = block->getComponent<Transform>();
                        auto &pos = tf.position;
                        auto &sz = tf.size;

                        BounceBlock bounce;
                        bounce.originalY = pos.y;
                        bounce.updateY = pos.y - (sz.y / 4);
                        block->addComponent<BounceBlock>(bounce);
                        pos.y = bounce.updateY;

                        continue;
                    }
                }
            }
        }
    }
};