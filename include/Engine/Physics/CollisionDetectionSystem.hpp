#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <Engine/Physics/SpatialHashGrid.hpp>
#include <Engine/Core/RigidBody.hpp>

class CollisionDetectionSystem : public System
{
private:
    SpatialHashGrid& grid = SpatialHashGrid::getInstance();
    const float MAX_DISTANCE = 2000.0f;

public:
    void update(World &world, float dt) override
    {
        grid.clear();
        auto entities = world.findAll<BoxCollider2D, Transform>();

        // // Not check the entities which are too far away from the screen center
        // if (auto camera = world.findFirst<Camera>())
        // {
        //     const auto &center = camera->getComponent<Camera>().target;
        //     sf::FloatRect viewArea(center - MAX_DISTANCE * sf::Vector2f(1, 1), MAX_DISTANCE * sf::Vector2f(2, 2));

        //     // std::cout << "Center: " << center.x << " " << center.y << "\n";

        //     entities.erase(
        //         std::remove_if(entities.begin(), entities.end(), [&](Entity* entity) {
        //             sf::FloatRect bounds = Physics::GetCollisionBounds(entity);
        //             return !entity->hasComponent<RigidBody>() && !viewArea.intersects(bounds);
        //         }),
        //         entities.end()
        //     );
        // }


        // Insert entities into spatial grid
        for (Entity *e : entities)
        {
            auto &col = e->getComponent<BoxCollider2D>();
            if (col.rotation != 0.0f)
                continue;

            auto &tf = e->getComponent<Transform>();
            sf::FloatRect bounds(tf.position + col.offset, col.size);
            grid.insert(e, bounds);
            col.collisions.clear();
        }

        for (Entity *e : entities)
        {
            auto &tf = e->getComponent<Transform>();
            auto &col = e->getComponent<BoxCollider2D>();
            sf::FloatRect bounds(tf.position + col.offset, col.size);

            auto nearby = grid.query(bounds);
            for (Entity *other : nearby)
            {
                if (e == other)
                    continue;

                if (!e->hasComponent<RigidBody>() && !other->hasComponent<RigidBody>()) continue;

                CollisionInfo info;
                if (e->hasComponent<RigidBody>() && other->hasComponent<RigidBody>())
                {
                    info = Physics::GetCollisionInfoMoving(e, other);
                }
                else
                {
                    info = Physics::GetCollisionInfoStatic(e, other);
                }

                if (info.collider)
                {
                    col.collisions.emplace_back(info);
                }
            }
        }
    }
};