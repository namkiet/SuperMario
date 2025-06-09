#pragma once
#include <SFML/Graphics.hpp>
#include <Components/Declaration.hpp>
#include <Entity.hpp>

class GravitySystem
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
            auto& gra = entity->getComponent<Gravity>();
            auto& rb = entity->getComponent<RigidBody>(); 
            
            auto g = gra.g;
            auto vel = rb.getVelocity();

            if (entity->hasComponent<Transform>())
            {
                auto pos = entity->getComponent<Transform>().getPosition();
                if (pos.y >= 200.f)
                {
                    vel.y = 0;
                    rb.setVelocity(vel);
                    return;
                }
            }

            
            vel.y += g * dt;
            rb.setVelocity(vel);
        }
    }   

private:
    std::vector<Entity*> entityList;
};