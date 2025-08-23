#pragma once

#include <cmath>

#include <CoinManager.hpp>

#include <ECS/System.hpp>
#include <Framework/World.hpp>

#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Factories/BlockFactory.hpp>
#include <Factories/ItemFactory.hpp>

#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

class HitSpecialBlockSystem : public System
{
private:
    void Hit1UpBlock(World &world, float dt, Entity *block);
    void HitQuestionBlock(World &world, float dt, Entity *block, Entity *player);
    void HitCoinBlock(World &world, float dt, Entity *block);
    void HitNormalBlock(World &world, float dt, Entity *block); // Only for large mario
    void HitStarBlock(World &world, float dt, Entity *block);
    void CoinBlockUpdate(World &world, float dt, Entity *block);
    void HitMushroomBlock(World &world, float dt, Entity *block);
    void HitLevelBlock(World &world, float dt, Entity *block);

    static sf::FloatRect getColliderBounds(Entity *entity)
    {
        const auto &tf = entity->getComponent<Transform>();
        const auto &box = entity->getComponent<BoxCollider2D>();

        return sf::FloatRect(tf.position + box.offset, box.size);
    }

public:
    void update(World &world, float dt) override
    {
        for (Entity *block : world.findAll<CoinBlockTag, CoinBlockComponent>())
        {
            CoinBlockUpdate(world, dt, block);
        }
        for (Entity *player : world.findAll<PlayerTag, BoxCollider2D, Transform>())
        {
            auto bounds1 = getColliderBounds(player);
            for (auto &[block, direction, overlap] : player->getComponent<BoxCollider2D>().collisions)
            {
                if (direction != Direction::Bottom)
                    continue;

                auto bounds2 = getColliderBounds(block);

                float left = std::fmax(bounds1.left, bounds2.left);
                float right = std::fmin(bounds1.left + bounds1.width, bounds2.left + bounds2.width);

                if (right - left < 0.5f * bounds1.width)
                    continue; // at least half of the size of the player must hit the block (to avoid hitting 2 blocks at the same time)
                if (!block->hasComponent<NormalBlockTag>() && !block->hasComponent<QuestionBlockTag>() &&
                    !block->hasComponent<CoinBlockTag>() && !block->hasComponent<StarBlockTag>() &&
                    !block->hasComponent<LevelUpBlockTag>() && !block->hasComponent<MushroomBlockTag>() &&
                    !block->hasComponent<LevelBlockTag>())
                    continue;

                // Normal Block
                if (block->hasComponent<NormalBlockTag>() && player->hasComponent<BigMarioTag>())
                {
                    // Remove NormalBlock component
                    block->removeComponent<NormalBlockTag>();

                    // This block can still kill enemy
                    block->removeComponent<Animation>();
                    block->removeComponent<BlockTag>();
                    block->addComponent<LifeSpan>(0.5f);
                    block->addComponent<CanKillEnemyTag>();

                    // Update
                    HitNormalBlock(world, dt, block);
                }
                else
                {
                    // Change texture of the block after hit
                    if (block->hasComponent<Animation>())
                    {
                        if (!block->hasComponent<NormalBlockTag>() && !block->hasComponent<CoinBlockTag>())
                            block->removeComponent<Animation>();
                    }
                    if (!block->hasComponent<NormalBlockTag>() && !block->hasComponent<CoinBlockTag>())
                    {
                        block->addComponent<Animation>(BlockFactory::getBlockTexture(27));
                    }

                    if (block->hasComponent<LevelUpBlockTag>())
                    {
                        // Remove LevelUpBlock component
                        block->addComponent<BlockTag>();
                        block->removeComponent<LevelUpBlockTag>();

                        // player->

                        // Update
                        Hit1UpBlock(world, dt, block);
                    }
                    else if (block->hasComponent<QuestionBlockTag>())
                    {
                        // Remove QuestionBlockTag component
                        block->removeComponent<QuestionBlockTag>();

                        // Update
                        HitQuestionBlock(world, dt, block, player);
                    }
                    else if (block->hasComponent<CoinBlockTag>())
                    {
                        // Remove CoinBlock component
                        // block->removeComponent<CoinBlockTag>();

                        // Update
                        HitCoinBlock(world, dt, block);

                        CoinManager::instance().addCoin();
                    }
                    else if (block->hasComponent<StarBlockTag>())
                    {
                        // Remove StarBlock component
                        block->removeComponent<StarBlockTag>();

                        // Update
                        HitStarBlock(world, dt, block);
                    }
                    else if (block->hasComponent<MushroomBlockTag>())
                    {
                        // Remove MushroomBlock component
                        block->removeComponent<MushroomBlockTag>();

                        // Update
                        HitMushroomBlock(world, dt, block);
                    }
                    else if (block->hasComponent<LevelBlockTag>())
                    {
                        // Remove LevelBlock component
                        block->removeComponent<LevelBlockTag>();

                        // Update
                        HitLevelBlock(world, dt, block);
                    }
                    if (block->hasComponent<Transform>() && !block->hasComponent<BounceBlockTag>())
                    {
                        auto &tf = block->getComponent<Transform>();
                        auto &pos = tf.position;
                        auto &sz = tf.size;

                        BounceBlockTag bounce;
                        bounce.originalY = pos.y;
                        block->addComponent<BounceBlockTag>(bounce);
                        block->addComponent<RigidBody>(sf::Vector2f(0, bounce.bounceVel), true);

                        continue;
                    }
                }
            }
        }
    }
};