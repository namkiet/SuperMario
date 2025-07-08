#pragma once
#include <World.hpp>
#include <Components/Input.hpp>
#include <Components/Transform.hpp>
#include <Components/RigidBody.hpp>

class PlayerMovementSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* player : world.findAll<PlayerTag>())
        {
            horizontalMovement(player, dt);
            verticalMovement(player, dt);
            applyGravity(player, dt);
            updatePosition(player, dt);
        }
    }

private:
    void horizontalMovement(Entity* player, float dt)
    {
        auto& input = player->getComponent<Input>();
        auto& vel = player->getComponent<RigidBody>().velocity;
        
        if (input.moveLeft)
        {
            vel.x = -moveSpeed;
        }
        else if (input.moveRight)
        {
            vel.x = moveSpeed;
        }
        else
        {
            vel.x = 0.0f;
        }
    }

    void verticalMovement(Entity* player, float dt)
    {
        auto& input = player->getComponent<Input>();
        auto& rb = player->getComponent<RigidBody>();
        if (input.jumpPressed && rb.onGround)
        {
            rb.velocity.y = -1280.0f;
        }
    }

    void applyGravity(Entity* player, float dt)
    {
        auto& vel = player->getComponent<RigidBody>().velocity;
        vel.y += gravity * dt;
    }

    void updatePosition(Entity* player, float dt)
    {
        auto& pos = player->getComponent<Transform>().position;
        auto& vel = player->getComponent<RigidBody>().velocity;
        pos += vel * dt;
    }

private:
    const float moveSpeed = 200.0f;
    const float gravity = 2560.0f;
};