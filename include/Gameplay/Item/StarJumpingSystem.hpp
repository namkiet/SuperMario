#pragma once
#include <World.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Prefabs/Star.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <fstream>
class StarJumpingSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        std::ofstream fout("output.txt", std::ios::app);
        if (fout.fail())
        {
            std::cerr << "Failed to open output.txt for writing." << std::endl;
            return;
        }
        for (Entity *star : world.findAll<StarTag, Transform, BoxCollider2D, RigidBody>())
        {
            auto &pos = star->getComponent<Transform>().position;
            auto &rb = star->getComponent<RigidBody>();
            auto &size = star->getComponent<Transform>().size;
            auto &collider = star->getComponent<BoxCollider2D>();
            auto &patrolComponent = star->getComponent<PatrolComponent>();
            for (const auto &[block, direction] : collider.collisions)
            {
                auto &blockPos = block->getComponent<Transform>().position;
                if (direction == Direction::Top)
                {
                    pos.y = blockPos.y - size.y * 2;
                    rb.velocity.y = 0.0f;
                    rb.velocity.x = 0.0f;
                    patrolComponent.moveSpeed = 400.0f;
                    // fout << "Star collided with block from bottom." << std::endl;
                }
                if (direction == Direction::Bottom)
                {
                    pos.y = blockPos.y + size.y * 2;
                }
                // fout << "Star collided with block from the top." << std::endl;
                if (direction == Direction::Left)
                    pos.x = blockPos.x - size.x;
                if (direction == Direction::Right)
                    pos.x = blockPos.x + size.x;
                // fout << "New star position: (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
        }
        fout.close();
    }
};