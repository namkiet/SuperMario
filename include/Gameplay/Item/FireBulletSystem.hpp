#pragma once
#include <World.hpp>
#include <Gameplay/Block/Components.hpp>
#include <Prefabs/Star.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <fstream>
#include <iostream>

class FireBulletSystem : public System
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

        for (Entity *fireBullet : world.findAll<FireBulletTag, Transform, BoxCollider2D, RigidBody>())
        {
            auto &pos = fireBullet->getComponent<Transform>().position;
            auto &rb = fireBullet->getComponent<RigidBody>();
            auto &size = fireBullet->getComponent<Transform>().size;
            auto &collider = fireBullet->getComponent<BoxCollider2D>();
            auto &patrolComponent = fireBullet->getComponent<PatrolComponent>();
            for (const auto &[block, direction] : collider.collisions)
            {
                if (block->hasComponent<PlayerTag>())
                    continue;
                auto &blockPos = block->getComponent<Transform>().position;
                auto &blockSize = block->getComponent<BoxCollider2D>().size;
                if (direction == Direction::Top && !block->hasComponent<StairsBlock>())
                {
                    pos.y = blockPos.y - size.y * 2;
                    rb.velocity.y = 0.0f;
                    rb.velocity.x = 0.0f;
                    patrolComponent.moveSpeed = 400.0f;
                    // std::cout << "FireBullet collided with block from the top." << std::endl;
                    // fout << "Star collided with block from bottom." << std::endl;
                }
                if (direction == Direction::Top)
                {
                    // pos.y = blockPos.y + size.y * 2;
                }
                // fout << "Star collided with block from the top." << std::endl;
                if ((direction == Direction::Left || direction == Direction::Right) && !block->hasComponent<GroundBlock>())
                {
                    // Remove the old animation
                    fireBullet->removeComponent<Animation>();

                    fireBullet->getComponent<BoxCollider2D>().size = sf::Vector2f(48, 48);
                    fireBullet->getComponent<Transform>().size = sf::Vector2f(48, 48);

                    // Add the new animation
                    fireBullet->addComponent<Animation>(TextureManager::load("assets/Item/FireBullet/FireBullet_4.png"));

                    // Add the life span component
                    fireBullet->addComponent<LifeSpan>(0.5f); // 1 second lifespan

                    // Stop the fire from moving
                    pos.x = blockPos.x + blockSize.x / 2;
                    fireBullet->getComponent<PatrolComponent>().moveSpeed = 0.0f;

                    // std::cout << "FireBullet collided with block from the side." << std::endl;
                    // pos.x = blockPos.x - size.x;
                }
                // fout << "New star position: (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
        }
        fout.close();
    }
};