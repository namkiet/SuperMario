#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Entity.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/Transform.hpp>

namespace Physics
{
    inline sf::Vector2f GetCollisionOverlap(Entity *a, Entity *b)
    {
        auto &boxA = a->getComponent<BoxCollider2D>();
        auto &boxB = b->getComponent<BoxCollider2D>();
        auto &tfA = a->getComponent<Transform>();
        auto &tfB = b->getComponent<Transform>();

        auto sizeA = boxA.size;
        auto sizeB = boxB.size;
        auto posA = tfA.position + boxA.offset + 0.5f * sizeA;
        auto posB = tfB.position + boxB.offset + 0.5f * sizeB;

        float dx = abs(posA.x - posB.x);
        float dy = abs(posA.y - posB.y);
        float xo = 0.5f * (sizeA.x + sizeB.x);
        float yo = 0.5f * (sizeA.y + sizeB.y);

        return sf::Vector2f(xo - dx, yo - dy);
    }

    inline bool isColliding(Entity *a, Entity *b)
    {
        sf::Vector2f overlap = GetCollisionOverlap(a, b);
        return overlap.x > 0.0f && overlap.y > 0.0f;
    }

    inline Direction GetCollisionDirection(Entity *a, Entity *b)
    {
        auto &boxA = a->getComponent<BoxCollider2D>();
        auto &boxB = b->getComponent<BoxCollider2D>();
        auto &tfA = a->getComponent<Transform>();
        auto &tfB = b->getComponent<Transform>();

        auto sizeA = boxA.size;
        auto sizeB = boxB.size;
        auto posA = tfA.position + boxA.offset + 0.5f * sizeA;
        auto posB = tfB.position + boxB.offset + 0.5f * sizeB;
        auto prevA = tfA.prevPos + boxA.offset + 0.5f * sizeA;
        auto prevB = tfB.prevPos + boxB.offset + 0.5f * sizeB;

        float dx = abs(posA.x - posB.x);
        float dy = abs(posA.y - posB.y);
        float dxPrev = abs(prevA.x - prevB.x);
        float dyPrev = abs(prevA.y - prevB.y);
        float xo = 0.5f * (sizeA.x + sizeB.x);
        float yo = 0.5f * (sizeA.y + sizeB.y);

        if (xo >= dx && yo >= dy)
        {
            if (yo > dyPrev)
            {
                if (prevA.x < posB.x)
                {
                    return Direction::Left;
                }
                else
                {
                    return Direction::Right;
                }
            }
            else if (xo > dx)
            {
                if (prevA.y < posB.y)
                {
                    return Direction::Top;
                }
                else
                {
                    return Direction::Bottom;
                }
            }
        }
        return Direction::None;
    }

    // inline CollisionInfo AABBOverlap2(Entity* a, Entity* b)
    // {
    //     auto& boxA = a->getComponent<BoxCollider2D>();
    //     auto& boxB = b->getComponent<BoxCollider2D>();
    //     auto& tfA = a->getComponent<Transform>();
    //     auto& tfB = b->getComponent<Transform>();

    //     auto sizeA = boxA.size;
    //     auto sizeB = boxB.size;
    //     auto posA = tfA.position + boxA.offset + 0.5f * sizeA;
    //     auto posB = tfB.position + boxB.offset + 0.5f * sizeB;
    //     auto prevA = tfA.prevPos + boxA.offset + 0.5f * sizeA;
    //     auto prevB = tfB.prevPos + boxB.offset + 0.5f * sizeB;

    //     float dx = abs(posA.x - posB.x);
    //     float dy = abs(posA.y - posB.y);
    //     float dxPrev = abs(prevA.x - prevB.x);
    //     float dyPrev = abs(prevA.y - prevB.y);
    //     float xo = 0.5f * (sizeA.x + sizeB.x);
    //     float yo = 0.5f * (sizeA.y + sizeB.y);

    //     CollisionInfo info;

    //     sf::Vector2f overlap(xo - dx, yo - dy);
    //     if (overlap.x > 0.0f && overlap.y > 0.0f)
    //     {
    //         info.overlap = overlap;
    //         info.collider = b;

    //         if (yo > dyPrev)
    //         {
    //             if (prevA.x < posB.x)
    //             {
    //                 info.direction = Direction::Left;
    //             }
    //             else
    //             {
    //                 info.direction = Direction::Right;
    //             }
    //         }
    //         else
    //         {
    //             if (prevA.y < posB.y)
    //             {
    //                 info.direction = Direction::Top;
    //             }
    //             else
    //             {
    //                 info.direction = Direction::Bottom;
    //             }
    //         }
    //     }

    //     return info;
    // }
}