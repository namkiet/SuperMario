#pragma once

#include <World.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Animation/Animation.hpp>

#include <Gameplay/Fire/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <Prefabs/FireBullet.hpp>

#include <Core/KeyPressPool.hpp>
#include <fstream>

class FireSystem : public System
{
private:
public:
    void update(World &world, float dt) override
    {
        for (Entity *player : world.findAll<CanFireTag, Transform, FireCooldown, RigidBody>())
        {
            auto &pos = player->getComponent<Transform>().position;
            auto &size = player->getComponent<Transform>().size;
            auto &pool = KeyPressPool::Instance();
            auto &cooldown = player->getComponent<FireCooldown>();

            // Update the cooldown time
            cooldown.timeCount += dt;

            player->removeComponent<ShootingTag>();
            if (pool.isKeyPressed(sf::Keyboard::M) && FireBullet::getCount() < 2 && cooldown.timeCount > 0.5f)
            {
                Entity *gameSession = world.findFirst<ThemeComponent>();
                if (!gameSession)
                    return;

                auto &themeComponent = gameSession->getComponent<ThemeComponent>();
                auto fireBullet = world.createEntity<FireBullet>(pos.x + size.x / 2, pos.y + size.y / 8, 24.0f, 24.0f, ItemFactory(themeComponent.currentTheme));
                player->addComponent<ShootingTag>();
                if (!player->hasComponent<FlipXTag>())
                {
                    if (fireBullet->hasComponent<PatrolComponent>())
                        fireBullet->getComponent<PatrolComponent>().isMovingRight = true;
                    if (fireBullet->hasComponent<Transform>())
                        fireBullet->getComponent<Transform>().position.x = pos.x + size.x;
                }
                else if (player->hasComponent<FlipXTag>())
                {
                    if (fireBullet->hasComponent<PatrolComponent>())
                        fireBullet->getComponent<PatrolComponent>().isMovingRight = false;
                    if (fireBullet->hasComponent<Transform>())
                        fireBullet->getComponent<Transform>().position.x = pos.x - fireBullet->getComponent<Transform>().size.x;
                }

                cooldown.timeCount = 0;
            }
        }
        // fout.close();
    }
};