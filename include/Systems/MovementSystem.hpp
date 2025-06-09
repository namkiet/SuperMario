#pragma once
#include <SFML/Graphics.hpp>
#include <Components/Declaration.hpp>
#include <Entity.hpp>

class MovementSystem
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
            auto& rb = entity->getComponent<RigidBody>();
            auto& tf = entity->getComponent<Transform>();

            auto vel = rb.getVelocity();
            auto pos = tf.getPosition();
            
            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            tf.setPosition(pos);

            // if (entity->hasComponent<BoxCollider2D>())
            // {
            //     auto& box = entity->getComponent<BoxCollider2D>();
            //     box.position = pos;
            // }
        }
    }

private:
    std::vector<Entity*> entityList;
};
