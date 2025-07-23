#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/PassThroughTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Item/Components.hpp>
#include <fstream>

class HitBlockSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        // std::ofstream fout("output.txt", std::ios::app);
        // if (fout.fail())
        // {
        //     std::cerr << "Failed to open output.txt for writing." << std::endl;
        //     return;
        // }
        for (Entity *entity : world.findAll<BoxCollider2D, Transform, RigidBody>())
        {
            if (entity->hasComponent<PassThroughTag>())
                continue;

            if (entity->hasComponent<StarTag>())
                continue;
            
            if (entity->hasComponent<FireBulletTag>())
                continue;
            
            const auto &box = entity->getComponent<BoxCollider2D>();
            auto &rb = entity->getComponent<RigidBody>();
            auto &tf = entity->getComponent<Transform>();

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
                    {
                        float finalPosY_Top = blockPos.y - box.size.y;
                        rb.velocity.y = (finalPosY_Top - tf.position.y) / dt;
                        rb.onGround = true;
                        //fout << "Entity collided with block from the top." << std::endl;
                    }
                    break;

                    case Direction::Bottom:
                    {
                        float finalPosY_Bottom = blockPos.y + blockSize.y;
                        rb.velocity.y = (finalPosY_Bottom - tf.position.y) / dt;
                        //fout<< "Entity collided with block from the bottom." << std::endl;
                    }
                    break;

                    case Direction::Left:
                    {
                        float finalPosX_Left = blockPos.x - box.size.x;
                        rb.velocity.x = (finalPosX_Left - tf.position.x) / dt;
                        //fout << "Entity collided with block from the left." << std::endl;
                    }
                    break;

                    case Direction::Right:
                    {
                        float finalPosX_Right = blockPos.x + blockSize.x;
                        rb.velocity.x = (finalPosX_Right - tf.position.x) / dt;
                        //fout << "Entity collided with block from the right." << std::endl;
                    }
                    break;

                    default:
                        break;
                }
            }
            // std::cout <<"at the end of hitblock, onGround = " << rb.onGround << std::endl;
        }
        // fout.close();
    }
};