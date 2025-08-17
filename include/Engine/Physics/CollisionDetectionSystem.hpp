#pragma once
#include <ECS/System.hpp>
#include <Core/Physics.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/SpatialHashGrid.hpp>
#include <Gameplay/Player/Components.hpp>
#include <World.hpp>
#include <Engine/Core/RigidBody.hpp>

class CollisionDetectionSystem : public System
{
private:
    SpatialHashGrid &grid = SpatialHashGrid::getInstance();
    const float MAX_DISTANCE = 2000.0f;
    bool obbIntersect(const sf::Vector2f *a, const sf::Vector2f *b);

    sf::FloatRect getOBBBounds(const sf::Vector2f *corners);
    sf::FloatRect getAABBBounds(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &offset);

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
            auto &tf = e->getComponent<Transform>();
            sf::FloatRect bounds;
            if (col.rotation == 0.0f)
                bounds = getAABBBounds(tf.position, col.size, col.offset);
            else
                bounds = getOBBBounds(col.corners);
            grid.insert(e, bounds);
            col.collisions.clear();
        }

        for (Entity *e : entities)
        {
            auto &tfA = e->getComponent<Transform>();
            auto &colA = e->getComponent<BoxCollider2D>();
            sf::FloatRect bounds;
            if (colA.rotation == 0.0f)
                bounds = getAABBBounds(tfA.position, colA.size, colA.offset);
            else
                bounds = getOBBBounds(colA.corners);

            auto nearby = grid.query(bounds);
            for (Entity *other : nearby)
            {
                if (e == other)
                    continue;

                if (!e->hasComponent<RigidBody>() && !other->hasComponent<RigidBody>())
                    continue;

                auto &colB = other->getComponent<BoxCollider2D>();
                auto &tfB = other->getComponent<Transform>();

                if (colA.rotation == 0.0f && colB.rotation == 0.0f) // AABB(A) vs AABB(B)
                {
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
                        colA.collisions.emplace_back(info);
                    }
                }
                else if (colA.rotation != 0.0f && colB.rotation == 0.0f) // OBB (A) vs AABB (B)
                {
                    sf::Vector2f aabbCorners[4];
                    aabbCorners[0] = tfB.position + colB.offset;
                    aabbCorners[1] = tfB.position + colB.offset + sf::Vector2f(colB.size.x, 0);
                    aabbCorners[2] = tfB.position + colB.offset + colB.size;
                    aabbCorners[3] = tfB.position + colB.offset + sf::Vector2f(0, colB.size.y);

                    if (obbIntersect(colA.corners, aabbCorners))
                    {
                        colA.collisions.emplace_back(CollisionInfo(other, Direction::Left));
                    }
                }
                else if (colA.rotation == 0.0f && colB.rotation != 0.0f) // AABB (A) vs OBB (B)
                {
                    sf::Vector2f aabbCorners[4];
                    aabbCorners[0] = tfA.position + colA.offset;
                    aabbCorners[1] = tfA.position + colA.offset + sf::Vector2f(colA.size.x, 0);
                    aabbCorners[2] = tfA.position + colA.offset + colA.size;
                    aabbCorners[3] = tfA.position + colA.offset + sf::Vector2f(0, colA.size.y);

                    if (obbIntersect(aabbCorners, colB.corners))
                    {
                        colA.collisions.emplace_back(CollisionInfo(other, Direction::Left));
                    }
                }
            }
        }
    }
};