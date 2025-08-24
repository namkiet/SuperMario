#pragma once
#include <Framework/World.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Core/Variables.hpp>
#include <LevelManager.hpp>
#include <iostream>
#include <Engine/Audio/SoundManager.hpp>

class MovementSystem : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<Transform>())
        {
            auto &tf = entity->getComponent<Transform>();
            tf.prevPos = tf.position;

            if (entity->hasComponent<RigidBody>())
            {
                auto &rb = entity->getComponent<RigidBody>();
                tf.position.x += rb.velocity.x * dt;
                tf.position.y += std::min(rb.velocity.y * dt, 100.0f);
            }
            if (tf.position.y > SIZE::SCREEN.y + 200.0f && !entity->hasComponent<DespawnTag>())
            {
                entity->addComponent<DespawnTag>();
                if (entity->hasComponent<PlayerTag>())
                {
                    std::cout << "player is out of screen\n";
                    // world.createEntity()->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/death.wav"), false, true, sf::Time(sf::seconds(0.5)));
                    LevelManager::instance().setPrevMarioPosition(tf.position);
                }
            }
        }
    }
};