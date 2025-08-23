#pragma once

#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>

#include <Factories/ItemFactory.hpp>

#include <Framework/World.hpp>

#include <Gameplay/Block/Components.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Gameplay/Patrol/Components.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Obstacles/Components.hpp>

class FireBulletSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *fireBullet : world.findAll<FireBulletTag, Transform, BoxCollider2D, RigidBody, PatrolComponent>())
        {
            auto &pos = fireBullet->getComponent<Transform>().position;
            auto &rb = fireBullet->getComponent<RigidBody>();
            auto &size = fireBullet->getComponent<Transform>().size;
            auto &collider = fireBullet->getComponent<BoxCollider2D>();
            auto &patrolComponent = fireBullet->getComponent<PatrolComponent>();

            // Get the camera position
            Entity *camera = world.findFirst<Camera>();
            if (camera)
            {
                auto cameraPos = camera->getComponent<Camera>().target.x + camera->getComponent<Camera>().trapHalfWidth;
                if (pos.x > cameraPos * 1.5f)
                {
                    fireBullet->addComponent<DespawnTag>();
                    continue;
                }
            }

            for (const auto &[block, direction, overlap] : collider.collisions)
            {
                if (block->hasComponent<LifeSpan>())
                    continue;

                if (block->hasComponent<PlayerTag>())
                    continue;

                if (block->hasComponent<FireBulletTag>())
                    continue;

                if (!block->hasComponent<BoxCollider2D>())
                    continue;

                if (!block->hasComponent<Transform>())
                    continue;

                if (block->hasComponent<FireBarComponent>())
                    continue;

                if (block->hasComponent<PodobooTag>())
                    continue;

                auto &blockPos = block->getComponent<Transform>().position;
                auto &blockSize = block->getComponent<BoxCollider2D>().size;

                if (direction == Direction::Top && !block->hasComponent<EnemyTag>())
                {
                    pos.y = blockPos.y - size.y * 2.5;
                    rb.velocity.y = -300.0f;

                    break;
                }

                // Resize the size
                fireBullet->getComponent<BoxCollider2D>().size = sf::Vector2f(48, 48);
                fireBullet->getComponent<Transform>().size = sf::Vector2f(48, 48);

                // Remove the old animation
                fireBullet->removeComponent<Animation>();

                // Set the new position
                if (direction == Direction::Left)
                    pos.x = blockPos.x - size.x + size.x / 4;
                else if (direction == Direction::Right)
                    pos.x = blockPos.x + blockSize.x;

                // Add the new animation
                fireBullet->addComponent<Animation>(ItemFactory::getItemTexture("fireworks"));

                // Add the life span component
                fireBullet->addComponent<LifeSpan>(0.3f);

                // Stop the firebullet from moving
                fireBullet->removeComponent<PatrolComponent>();
                fireBullet->removeComponent<RigidBody>();
            }
        }
    }
};