#pragma once
#include <World.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Prefabs/FireBullet.hpp>
#include <Gameplay/Item/Components.hpp>
#include <Engine/Core/Transform.hpp>

#include <Core/KeyPressPool.hpp>
#include <fstream>

class FireSystem : public System
{
private:
    int timeCount = 0;

public:
    void update(World &world, float dt) override
    {
        // std::ofstream fout("output.txt", std::ios::app);
        // if (fout.fail())
        // {
        //     std::cerr << "Failed to open output.txt for writing." << std::endl;
        //     return;
        // }

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
                auto fireBullet = world.createEntity<FireBullet>(pos.x + size.x / 2, pos.y + size.y / 8, 24, 24);

                timeCount = 10;

                // fout << "Fired a fire bullet at position: " << pos.x - size.x / 2 << " " << pos.y + size.y / 8 << std::endl;
            }
        }
        // fout.close();
    }
};