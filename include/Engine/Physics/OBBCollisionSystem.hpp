#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <iostream>
class OBBCollisionSystem : public System
{
private:
    bool obbIntersect(const sf::Vector2f *a, const sf::Vector2f *b)
    {
        // Check all axes (edges of both boxes)
        for (int box = 0; box < 2; ++box)
        {
            const sf::Vector2f *verts = (box == 0) ? a : b;
            for (int i = 0; i < 4; ++i)
            {
                // Edge vector
                sf::Vector2f edge = verts[(i + 1) % 4] - verts[i];
                // Perpendicular axis
                sf::Vector2f axis(-edge.y, edge.x);

                // Project both boxes onto axis
                float minA = INFINITY, maxA = -INFINITY;
                float minB = INFINITY, maxB = -INFINITY;
                for (int j = 0; j < 4; ++j)
                {
                    float projA = a[j].x * axis.x + a[j].y * axis.y;
                    float projB = b[j].x * axis.x + b[j].y * axis.y;
                    minA = std::min(minA, projA);
                    maxA = std::max(maxA, projA);
                    minB = std::min(minB, projB);
                    maxB = std::max(maxB, projB);
                }
                if (maxA < minB || maxB < minA)
                    return false; // Separating axis found
            }
        }
        return true; // No separating axis, boxes intersect
    }

public:
    void update(World &world, float dt) override
    {
        auto entities = world.findAll<BoxCollider2D, Transform>();
        for (Entity *e : entities)
        {
            auto &colA = e->getComponent<BoxCollider2D>();
            auto &tfA = e->getComponent<Transform>();

            for (Entity *other : entities)
            {
                if (e == other)
                    continue;
                auto &colB = other->getComponent<BoxCollider2D>();
                auto &tfB = other->getComponent<Transform>();

                // OBB (A) vs AABB (B)
                if (colA.rotation != 0.0f && colB.rotation == 0.0f)
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
                // AABB (A) vs OBB (B)
                else if (colA.rotation == 0.0f && colB.rotation != 0.0f)
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