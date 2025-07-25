#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Item/Components.hpp>
class HitBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<CanHitBlockTag, BoxCollider2D, Transform, RigidBody>())
        {
            const auto &box = entity->getComponent<BoxCollider2D>();
            auto &rb = entity->getComponent<RigidBody>();
            auto &tf = entity->getComponent<Transform>();

            if (entity->hasComponent<StarTag>())
                continue;
            if (entity->hasComponent<FireBulletTag>())
                continue;
            rb.onGround = false;
            for (auto &[block, direction] : box.collisions)
            {
                // Check if the entity it collides with is solid
                if (!block->hasComponent<BlockTag>())
                    continue;
                if (!block->hasComponent<BoxCollider2D>())
                    continue;
                if (!block->hasComponent<Transform>())
                    continue;

                const auto &blockPos = block->getComponent<Transform>().position + block->getComponent<BoxCollider2D>().offset;
                const auto &blockSize = block->getComponent<BoxCollider2D>().size;
                switch (direction)
                {
                case Direction::Top:
                    tf.position.y = blockPos.y - box.size.y;
                    rb.velocity.y = 0.0f;
                    rb.onGround = true;
                    break;

                case Direction::Bottom:
                    if (!block->hasComponent<PipeTag>())
                    {
                        // If the block is not passable, set the position to the bottom of the block
                        tf.position.y = blockPos.y + blockSize.y;
                        rb.velocity.y = 0.0f;
                    }
                    break;

                case Direction::Left:
                    tf.position.x = blockPos.x - box.size.x;
                    rb.velocity.x = 0.0f;
                    break;

                case Direction::Right:
                    tf.position.x = blockPos.x + blockSize.x - box.offset.x;
                    rb.velocity.x = 0.0f;
                    break;

                default:
                    break;
                }
            }
        }
    }
};