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

#include <Engine/Animation/Animation.hpp>

class HitBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<CanHitBlockTag, BoxCollider2D, Transform, RigidBody>())
        {
            if (entity->hasComponent<StarTag>()) continue;
            if (entity->hasComponent<FireBulletTag>()) continue;

            auto &box = entity->getComponent<BoxCollider2D>();
            auto &tf = entity->getComponent<Transform>();
            auto &rb = entity->getComponent<RigidBody>();
            rb.onGround = false;

            for (auto &[block, direction, overlap] : box.collisions)
            {
                // Check if the entity it collides with is solid
                if (!block->hasComponent<BlockTag>()) continue;
                if (!block->hasComponent<BoxCollider2D>()) continue;
                if (!block->hasComponent<Transform>()) continue;

                // Avoid wall stuck
                if (shouldSkipToAvoidStuck(block, direction, box.collisions)) continue;

                auto blockVel = block->hasComponent<RigidBody>() ? block->getComponent<RigidBody>().velocity : sf::Vector2f(0, 0);
                auto blockPos = block->getComponent<Transform>().position + block->getComponent<BoxCollider2D>().offset;
                auto blockSize = block->getComponent<BoxCollider2D>().size;

                switch (direction)
                {
                    case Direction::Top:
                        tf.position.y = blockPos.y - box.size.y - box.offset.y;
                        rb.velocity.y = blockVel.y;
                        rb.onGround = true;
                        break;

                    case Direction::Bottom:
                        tf.position.y = blockPos.y + blockSize.y - box.offset.y;
                        rb.velocity.y = std::fmax(blockVel.y, 0.0f);
                        break;

                    case Direction::Left:
                        tf.position.x = blockPos.x - box.size.x - box.offset.x;
                        rb.velocity.x = std::fmin(blockVel.y, 0.0f);
                        break;

                    case Direction::Right:
                        tf.position.x = blockPos.x + blockSize.x - box.offset.x;
                        rb.velocity.x = std::fmax(blockVel.y, 0.0f);
                        break;

                    default:
                        break;
                }
            }
        }
    }

private:
    bool shouldSkipToAvoidStuck(Entity* curBlock, const Direction& curDir, const std::vector<CollisionInfo>& otherCollisions)
    {
        if (curDir != Direction::Top && curDir != Direction::Bottom) return false;
        auto bounds1 = Physics::GetCollisionBounds(curBlock);
        for (auto& [other, dir2, _] : otherCollisions)
        {
            auto bounds2 = Physics::GetCollisionBounds(other);
            if (dir2 == Direction::Left && bounds1.left == bounds2.left) return true;
            if (dir2 == Direction::Right && bounds1.left + bounds1.width == bounds2.left + bounds2.width) return true;
        }
        return false;
    }
};