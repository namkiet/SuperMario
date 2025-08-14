#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <cmath>
bool CollisionDetectionSystem::obbIntersect(const sf::Vector2f *a, const sf::Vector2f *b)
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

sf::FloatRect CollisionDetectionSystem::getOBBBounds(const sf::Vector2f *corners)
{
    float minX = corners[0].x, maxX = corners[0].x;
    float minY = corners[0].y, maxY = corners[0].y;
    for (int i = 1; i < 4; ++i)
    {
        minX = std::min(minX, corners[i].x);
        maxX = std::max(maxX, corners[i].x);
        minY = std::min(minY, corners[i].y);
        maxY = std::max(maxY, corners[i].y);
    }
    return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
}

sf::FloatRect CollisionDetectionSystem::getAABBBounds(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &offset)
{
    return sf::FloatRect(position + offset, size);
}