#pragma once
#include <World.hpp>
#include <Components/Input.hpp>
#include <Components/Transform.hpp>
#include <Components/RigidBody.hpp>
#include <Core/Variables.hpp>

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
            auto& anim = player->getComponent<Animation>();
            anim.flipX = true;
        }
        else if (input.moveRight)
        {
            vel.x = moveSpeed;
            auto& anim = player->getComponent<Animation>();
            anim.flipX = false;
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
            rb.velocity.y = -1500.0f;
            std::cout << "HELLO\n";
        }
    }

    void applyGravity(Entity* player, float dt)
    {
        auto& rb = player->getComponent<RigidBody>();
        rb.velocity.y += gravity * dt;
    }

    void updatePosition(Entity* player, float dt)
    {
        auto& pos = player->getComponent<Transform>().position;
        auto& vel = player->getComponent<RigidBody>().velocity;
        auto& acc = player->getComponent<RigidBody>().acceleration;

        // vel += acc * dt;

        // auto& rb = player->getComponent<RigidBody>();
        // std::cout << rb.acceleration.x << " " << rb.acceleration.y << "\n";
        // std::cout << vel.x << " " << vel.y << "\n";


        vel.x = std::fmin(vel.x, 1500.0f);
        vel.x = std::fmax(vel.x, -1500.0f);
        vel.y = std::fmin(vel.y, 1500.0f);
        vel.y = std::fmax(vel.y, -1500.0f);

        if (pos.y >= SIZE::SCREEN.y)
        {
            player->addComponent<DeadTag>();
        }

        pos += vel * dt;

    }

private:
    const float moveSpeed = 200.0f;
    const float gravity = 3000.0f;
};

