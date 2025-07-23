#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/HitBlock/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Core/TextureManager.hpp>
#include <Prefabs/Coin.hpp>
#include <iostream>

class HitCoinBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        // Update timer for all coin blocks
        for (Entity *block : world.findAll<CoinBlock, CoinBlockComponent>())
        {
            auto &coinBlockComponent = block->getComponent<CoinBlockComponent>();

            if (!coinBlockComponent.firstTime)
                continue;
            coinBlockComponent.timer += dt;

            if (coinBlockComponent.timer >= coinBlockComponent.waitingTime)
            {
                coinBlockComponent.hitCount = 1;
            }
            if (coinBlockComponent.isCollected)
            {
                block->removeComponent<CoinBlock>();
                block->removeComponent<CoinBlockComponent>();
                block->removeComponent<Animation>();
                block->addComponent<Animation>(TextureManager::load("assets/Tile/Tile1/Tile1_27.png"));
            }
        }

        // std::cout << "HitCoinBlockSystem update" << std::endl;
        for (Entity *entity : world.findAll<BoxCollider2D, CanHitCoinBlockTag>())
        {
            for (auto &[block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<CoinBlock>())
                    continue;

                if (direction != Direction::Bottom)
                    continue;

                if (!block->hasComponent<CoinBlockComponent>())
                {
                    continue;
                }

                auto &collected = block->getComponent<CoinBlockComponent>().isCollected;
                auto &coinBlockComponent = block->getComponent<CoinBlockComponent>();

                if (!coinBlockComponent.firstTime)
                    coinBlockComponent.firstTime = true;

                if (block->hasComponent<Transform>())
                {
                    auto &tf = block->getComponent<Transform>();
                    auto &pos = tf.position;
                    auto &sz = tf.size;

                    // For small mario -> move up
                    if (!block->hasComponent<BounceBlock>())
                    {
                        BounceBlock bounce;
                        bounce.originalY = pos.y;
                        bounce.updateY = pos.y - (sz.y / 4);
                        block->addComponent<BounceBlock>(bounce);
                        pos.y = bounce.updateY;
                    }
                    // std::cout << "CoinBlockComponent hitCount: " << coinBlockComponent.hitCount << std::endl;
                    if (coinBlockComponent.hitCount > 0)
                    {
                        world.createEntity<Coin1>(pos.x, pos.y - sz.y, 48, 48);

                        coinBlockComponent.timer = 0.0f;
                        --coinBlockComponent.hitCount;
                        // std::cout << "Coin create" << std::endl;
                        // std::cout << "CoinBlockComponent hitCount: " << coinBlockComponent.hitCount << std::endl;
                        if (coinBlockComponent.hitCount <= 0)
                        {
                            collected = true;
                        }
                    }
                }
            }
        }
    }
};