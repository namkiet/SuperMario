#pragma once

#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>

#include <World.hpp>

class FireBulletSystem : public System
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

        for (Entity *fireBullet : world.findAll<FireBulletTag, Transform, BoxCollider2D, RigidBody, PatrolComponent>())
        {
            auto &pos = fireBullet->getComponent<Transform>().position;
            auto &rb = fireBullet->getComponent<RigidBody>();
            auto &size = fireBullet->getComponent<Transform>().size;
            auto &collider = fireBullet->getComponent<BoxCollider2D>();
            auto &patrolComponent = fireBullet->getComponent<PatrolComponent>();
            for (const auto &[block, direction, overlap] : collider.collisions)
            {
                if (block->hasComponent<PlayerTag>())
                {
                    // fout << "FireBullet collided with player." << std::endl;
                    continue;
                }
                if (block->hasComponent<FireBulletTag>())
                {
                    // fout << "FireBullet collided with another FireBullet." << std::endl;
                    continue;
                }
                // fout << "Fire Bullet collided with blocks" << std::endl;
                auto &blockPos = block->getComponent<Transform>().position;
                auto &blockSize = block->getComponent<BoxCollider2D>().size;
                if (direction == Direction::Top && !block->hasComponent<StairsBlock>())
                {
                    if (block->hasComponent<PlayerTag>())
                    {
                        // fout << "FireBullet collided with player in direction top." << std::endl;
                        continue;
                    }
                    if (block->hasComponent<FireBulletTag>())
                    {
                        // fout << "FireBullet collided with another FireBullet." << std::endl;
                        continue;
                    }

                    pos.y = blockPos.y - size.y * 2.5;
                    rb.velocity.y = -200.0f;
                    // rb.velocity.x = 0.0f;
                    patrolComponent.moveSpeed = 600.0f;
                }
                if (direction == Direction::Bottom)
                {
                    // pos.y = blockPos.y + size.y * 2;
                }
                // fout << "Star collided with block from the top." << std::endl;
                if ((direction == Direction::Left || direction == Direction::Right) && !block->hasComponent<GroundBlock>())
                {
                    if (block->hasComponent<PlayerTag>())
                    {
                        // fout << "FireBullet collided with player in direction left/ right." << std::endl;
                        continue;
                    }
                    if (block->hasComponent<FireBulletTag>())
                    {
                        // fout << "FireBullet collided with another FireBullet." << std::endl;
                        continue;
                    }

                    if (fireBullet->hasComponent<LifeSpan>())
                    {
                        continue;
                    }

                    fireBullet->getComponent<BoxCollider2D>().size = sf::Vector2f(48, 48);
                    fireBullet->getComponent<Transform>().size = sf::Vector2f(48, 48);

                    // Remove the old animation
                    fireBullet->removeComponent<Animation>();

                    // Set the new position
                    if (direction == Direction::Left)
                    {
                        pos.x = blockPos.x - size.x + size.x / 4;
                    }
                    else if (direction == Direction::Right)
                    {
                        pos.x = blockPos.x + blockSize.x;
                    }

                    // Add the new animation
                    Entity *gameSession = world.findFirst<ThemeComponent>();
                    if (!gameSession)
                        return;
                    auto &themeComponent = gameSession->getComponent<ThemeComponent>();
                    ItemFactory itemFactory(themeComponent.currentTheme);
                    fireBullet->addComponent<Animation>(itemFactory.getItemTexture("fireworks"));

                    // Add the life span component
                    fireBullet->addComponent<LifeSpan>(0.3f);

                    // Stop the fire from moving
                    // pos.x = blockPos.x + blockSize.x / 2;
                    fireBullet->removeComponent<PatrolComponent>();

                    fireBullet->removeComponent<RigidBody>();

                    break;

                    // rb.velocity.x = 0.0f;
                    // rb.velocity.y = 0.0f;

                    // fout << "FireBullet collided with block from the side." << std::endl;
                    // fout << "New fire bullet position: (" << pos.x << ", " << pos.y << ")" << std::endl;
                }
                // fout << "New star position: (" << pos.x << ", " << pos.y << ")" << std::endl;
            }
        }
        // fout.close();
    }
};