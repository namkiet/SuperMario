#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/Player/Components.hpp>
#include <SFML/Graphics.hpp>

class PlayerInputSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* player : world.findAll<PlayerTag, RigidBody>())
        {
            auto& rb = player->getComponent<RigidBody>();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Move left
            {
                rb.velocity.x = -200.f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Move right
            {
                rb.velocity.x = 200.f;
            }
            else // Stading
            {
                rb.velocity.x = 0.f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && rb.onGround) // Jump
            {
                rb.velocity.y = -PHYSICS::JUMP_FORCE;
            }
        }
    }
};