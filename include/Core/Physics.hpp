#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Entity.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/Transform.hpp>
#include <iostream>
#include <Gameplay/Player/Components.hpp>

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
        if (!a->hasComponent<BoxCollider2D>() || 
            !b->hasComponent<BoxCollider2D>() || 
            !a->hasComponent<Transform>() || 
            !b->hasComponent<Transform>())
        {
            return Direction::None;
        }
        
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
// if (a->hasComponent<PlayerTag>())
//                     {
//                         std::cout << "prevA.y " << prevA.y << std::endl;
//                         std::cout << "posB.y " << posB.y << std::endl;
//                         std::cout << "posA.y " << posA.y << std::endl;
//                         std::cout << "prevB.y = " << prevB.y << std::endl; 
//                     }
        if (xo >= dx && yo >= dy)
        {
            // if (a->hasComponent<PlayerTag>())
            // {
            // std::cout << "xo = " << xo << std::endl;
            // std::cout << "yo = " << yo << std::endl;
            // std::cout << "dx = " << dx << std::endl;
            // std::cout << "dy = " << dy << std::endl;
            // }

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
                    // if (a->hasComponent<PlayerTag>())
                    //     std::cout << "collide right here" << std::endl;
                    return Direction::Bottom;

                }
            }
        }
        // if (a->hasComponent<PlayerTag>())
        //     std::cout << "it should be none" << std::endl;
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