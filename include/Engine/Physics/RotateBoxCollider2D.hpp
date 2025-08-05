#pragma once
#include <ECS/System.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/Transform.hpp>
#include <World.hpp>

class RotateBoxCollider2D : public System
{
public:
    void update(World &world, float dt) override
    {
        for (Entity *entity : world.findAll<BoxCollider2D, Transform>())
        {
            auto &box = entity->getComponent<BoxCollider2D>();
            auto &tf = entity->getComponent<Transform>();
            if (box.rotation == 0.0f)
                continue;

            box.origin = sf::Vector2f(box.size.x / 2, 12);
            sf::Vector2f worldOrigin = tf.position + box.offset + box.origin;
            float angleRad = box.rotation * 3.14159265f / 180.0f;
            sf::Vector2f halfSize = box.size * 0.5f;

            // Local corners
            sf::Vector2f local[4] = {
                -box.origin,
                sf::Vector2f(box.size.x, 0) - box.origin,
                sf::Vector2f(box.size.x, box.size.y) - box.origin,
                sf::Vector2f(0, box.size.y) - box.origin};

            // Rotate and translate to world space
            for (int i = 0; i < 4; ++i)
            {
                float x = local[i].x, y = local[i].y;
                box.corners[i].x = worldOrigin.x + x * std::cos(angleRad) - y * std::sin(angleRad);
                box.corners[i].y = worldOrigin.y + x * std::sin(angleRad) + y * std::cos(angleRad);
            }
        }
    }
};