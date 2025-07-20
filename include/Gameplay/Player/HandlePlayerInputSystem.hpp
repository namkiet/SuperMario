#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/Player/Components.hpp>
#include <SFML/Graphics.hpp>
#include <Core/Variables.hpp>
#include <Core/KeyPressPool.hpp>
#include <cassert>
class HandlePlayerInputSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* player : world.findAll<PlayerTag, RigidBody, InputTag>())
        {
            auto& rb = player->getComponent<RigidBody>();
            auto& pool = KeyPressPool::Instance();
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Move left
            // {
            //     rb.velocity.x = -200.f;
            // }
            // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Move right
            // {
            //     rb.velocity.x = 200.f;
            // }
            // else // Stading
            // {
            //     rb.velocity.x = 0.f;
            // }

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && rb.onGround) // Jump
            // {
            //     rb.velocity.y = -PHYSICS::JUMP_FORCE;
            // }

            if (pool.isKeyPressed(sf::Keyboard::A)) // Move left
            {
                rb.velocity.x -= PLAYER::HORIZONTAL_SPEED;
            }
            else if (pool.isKeyPressed(sf::Keyboard::D)) // Move right
            {
                rb.velocity.x += PLAYER::HORIZONTAL_SPEED;
            }

            if (pool.isKeyPressed(sf::Keyboard::W) && rb.onGround) // Jump
            {
                rb.velocity.y = -PHYSICS::JUMP_FORCE;
            }
            // gravity se detect theo thu tu nao
            
            // collision system detect bang cach xem vi tri hien tai
            // vay thay vi prevPos va curPos, su dung curPos va velocity thoi
            // bat dau phase thi curPos la vi tri hien tai, sau do cac logic system lien tuc dieu chinh velocity
        }
    }
};