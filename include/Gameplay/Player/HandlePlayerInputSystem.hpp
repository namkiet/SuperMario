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
#include <UI/KeyBinding.hpp>
class HandlePlayerInputSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* player : world.findAll<PlayerTag, RigidBody, InputTag>())
        {
            auto& tag = player->getComponent<PlayerTag>();
            auto& rb = player->getComponent<RigidBody>();
            auto& pool = KeyPressPool::Instance();
            
            auto& keybinding = KeyBinding::Instance();

            if (pool.isKeyPressed(keybinding.getKey(KeyBinding::Action::MoveLeft))) // Move left
            {
                rb.velocity.x = -tag.speed;
            }
            else if (pool.isKeyPressed(keybinding.getKey(KeyBinding::Action::MoveRight))) // Move right
            {
                rb.velocity.x = tag.speed;
            }
            else // Standing
            {
                rb.velocity.x = 0.f;
            }

            if (pool.isKeyPressed(keybinding.getKey(KeyBinding::Action::MoveUp)) && rb.onGround) // Jump
            {
                player->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/jumpsmall.wav"));
                rb.velocity.y = -tag.jumpForce;
            }
            // gravity se detect theo thu tu nao
            
            // collision system detect bang cach xem vi tri hien tai
            // vay thay vi prevPos va curPos, su dung curPos va velocity thoi
            // bat dau phase thi curPos la vi tri hien tai, sau do cac logic system lien tuc dieu chinh velocity
        }
    }
};