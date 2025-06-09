#pragma once
#include <SFML/Graphics.hpp>
#include <Components/Declaration.hpp>
#include <Entity.hpp>

class PlayerControlSystem
{
public:
    void addEntity(Entity* entity)
    {
        entityList.push_back(entity);
    }

    void update(float dt)
    {
        for (Entity* entity : entityList)
        {
            auto& input = entity->getComponent<Input>();
            auto& rb = entity->getComponent<RigidBody>();

            auto vel = rb.getVelocity();

            if (input.moveLeft)
            {
                vel.x = -100.f;
            } 
            else if (input.moveRight)
            {
                vel.x = 100.f;
            }
            else
            {
                vel.x = 0.f;
            }

            if (input.jumpPressed)
            {
                vel.y = -50.f;
            }

            rb.setVelocity(vel);
        }
    }   

private:
    std::vector<Entity*> entityList;
};