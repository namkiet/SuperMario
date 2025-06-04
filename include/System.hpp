#pragma once

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

            tf.setPosition(pos + sf::Vector2f(vel.x * dt, vel.y * dt));
        }
    }

private:
    std::vector<Entity*> entityList;
};

class RenderSystem
{
public:
    void addEntity(Entity* entity)
    {
        entityList.push_back(entity);
    }

    void draw(sf::RenderWindow& window) const
    {
        for (Entity* entity : entityList)
        {
            auto pos = entity->getComponent<Transform>().getPosition();
            auto shape = entity->getComponent<Sprite2D>().getShape();
            shape.setPosition(pos);

            window.draw(shape);
        }
    }

private:
    std::vector<Entity*> entityList;
};