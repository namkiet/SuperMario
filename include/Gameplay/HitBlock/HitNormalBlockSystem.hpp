#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Block/BounceBlock.hpp>
#include <Gameplay/HitBlock/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Prefabs/Debris.hpp>
#include <iostream>
class HitNormalBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        // std::cout << "HitNormalBlockSystem update called" << std::endl;
        for (Entity *entity : world.findAll<BoxCollider2D, CanHitNormalBlockTag>())
        {
            for (auto &[block, direction] : entity->getComponent<BoxCollider2D>().collisions)
            {
                if (!block->hasComponent<NormalBlock>())
                    continue;

                if (direction != Direction::Bottom)
                    continue;

                block->removeComponent<NormalBlock>();
                block->addComponent<DespawnTag>();
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

                    world.createEntity<SmallDebris1>(pos.x, pos.y, 24, 24);
                    world.createEntity<SmallDebris2>(pos.x, pos.y, 24, 24);
                    world.createEntity<SmallDebris3>(pos.x, pos.y, 24, 24);
                    world.createEntity<SmallDebris4>(pos.x, pos.y, 24, 24);
                }
            }
        }
    }
};