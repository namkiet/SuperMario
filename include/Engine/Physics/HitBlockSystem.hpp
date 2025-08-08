#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/SpatialHashGrid.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Item/Components.hpp>

class HitBlockSystem : public System
{
// private:
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<CanHitBlockTag, BoxCollider2D, Transform, RigidBody>())
        {
            const auto &box = entity->getComponent<BoxCollider2D>();
            auto &rb = entity->getComponent<RigidBody>();
            auto &tf = entity->getComponent<Transform>();

            if (entity->hasComponent<StarTag>()) continue;
            if (entity->hasComponent<FireBulletTag>()) continue;

            rb.onGround = false;

            for (auto &[block, direction, overlap] : box.collisions)
            {
                // Check if the entity it collides with is solid
                if (!block->hasComponent<BlockTag>()) continue;
                if (!block->hasComponent<BoxCollider2D>()) continue;
                if (!block->hasComponent<Transform>()) continue;

                const auto &blockPos = block->getComponent<Transform>().position + block->getComponent<BoxCollider2D>().offset;
                const auto &blockSize = block->getComponent<BoxCollider2D>().size;

                // if (box.collisions.size() > 1 && (direction == Direction::Top || direction == Direction::Bottom))
                // {
                //     bool shouldPass = false;

                //     auto entiesAbove = SpatialHashGrid::getInstance().query(blockPos + sf::Vector2f(10, -10));
                //     for (Entity* e : entiesAbove)
                //     {
                //         exit(0);
                //         if  (e == block) continue;
                //         if (!e->hasComponent<BlockTag>()) continue;
                //         if (!e->hasComponent<BoxCollider2D>()) continue;
                //         if (!e->hasComponent<Transform>()) continue;
                //         if (e->hasComponent<RigidBody>()) continue;

                //         auto ePos = e->getComponent<Transform>().position + e->getComponent<BoxCollider2D>().offset;

                //         if (ePos.x == blockPos.x && ePos.y < blockPos.y)
                //         {
                //             shouldPass = true;
                //             break;
                //         }
                //     }

                //     if (shouldPass) continue;
                // }

                switch (direction)
                {
                    case Direction::Top:
                        tf.position.y = blockPos.y - box.size.y;
                        rb.velocity.y = 0.0f;
                        rb.onGround = true;
                        break;

                    case Direction::Bottom:
                        tf.position.y = blockPos.y + blockSize.y;
                        rb.velocity.y = 0.0f;
                        break;

                    case Direction::Left:
                        tf.position.x = blockPos.x - box.size.x - box.offset.x;
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