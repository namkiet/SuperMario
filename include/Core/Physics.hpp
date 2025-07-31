#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Entity.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/Transform.hpp>
#include <iostream>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>

namespace Physics
{
    inline sf::FloatRect GetCollisionBounds(const sf::Vector2f& pos, const BoxCollider2D& box)
    {
        return sf::FloatRect(pos + box.offset, box.size);
    }

    inline sf::FloatRect GetCollisionBounds(Entity* e)
    {
        if (!e->hasComponent<BoxCollider2D>() || !e->hasComponent<Transform>())
        {
            return sf::FloatRect(0, 0, 0, 0);
        }

        return GetCollisionBounds(e->getComponent<Transform>().position, e->getComponent<BoxCollider2D>());
    }


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

    inline CollisionInfo GetCollisionInfo(Entity *a, Entity *b)
    {
        if (!a->hasComponent<BoxCollider2D>() || 
            !b->hasComponent<BoxCollider2D>() || 
            !a->hasComponent<Transform>() || 
            !b->hasComponent<Transform>())
        {
            return CollisionInfo();
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

        auto boundsA = GetCollisionBounds(a);
        auto boundsB = GetCollisionBounds(b);
        Direction dir;
        sf::FloatRect overlap;
        if (boundsA.intersects(boundsB, overlap))
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
                dir = prevA.x < prevB.x ? Direction::Left : Direction::Right;
            }
            else
            {
                dir = prevA.y < prevB.y ? Direction::Top : Direction::Bottom;
            }

            return CollisionInfo(b, dir, overlap);
        }
        return CollisionInfo();
    }
}