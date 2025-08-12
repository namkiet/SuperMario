#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
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
        for (Entity* player : world.findAll<RigidBody, InputTag>())
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
                rb.velocity.x = -PLAYER::HORIZONTAL_SPEED;
            }
            else if (pool.isKeyPressed(sf::Keyboard::D)) // Move right
            {
                rb.velocity.x = PLAYER::HORIZONTAL_SPEED;
            }
            else // Standing
            {
                rb.velocity.x = 0.f;
            }

            if (pool.isKeyPressed(sf::Keyboard::W) && rb.onGround) // Jump
            {
                player->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/jumpsmall.wav"));
                rb.velocity.y = -PHYSICS::JUMP_FORCE;
            }
            // gravity se detect theo thu tu nao
            
            // collision system detect bang cach xem vi tri hien tai
            // vay thay vi prevPos va curPos, su dung curPos va velocity thoi
            // bat dau phase thi curPos la vi tri hien tai, sau do cac logic system lien tuc dieu chinh velocity
        }
    }
};