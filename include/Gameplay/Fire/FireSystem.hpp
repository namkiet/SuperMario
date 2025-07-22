#pragma once
#include <World.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Prefabs/FireBullet.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Core/KeyPressPool.hpp>

class FireSystem : public System
{
private:
    int timeCount = 0;

public:
    void update(World &world, float dt) override
    {
        --timeCount;
            
        for (Entity *entity : world.findAll<CanFireTag, Transform>())
        {
            auto &pos = entity->getComponent<Transform>().position;
            auto &size = entity->getComponent<Transform>().size;
            auto &pool = KeyPressPool::Instance();

            // cout << FireBullet::getCount() << endl;
            if (pool.isKeyPressed(sf::Keyboard::M) && FireBullet::getCount() < 2 && timeCount <= 0)
            {
                // std::cout << "Firing bullet at position: " << pos.x << ", " << pos.y << std::endl;
                auto fireBullet = world.createEntity<FireBullet>(pos.x - size.x / 2, pos.y + size.y / 8, 24, 24);
                fireBullet->addComponent<BoxCollider2D>(sf::Vector2f(24, 24));

                fireBullet->addComponent<PatrolComponent>();
                fireBullet->getComponent<PatrolComponent>().moveSpeed = 200.0f;

                fireBullet->addComponent<RigidBody>(sf::Vector2f(0, 50));

                timeCount = 10;
            }
        }
    }
};