#pragma once
#include <World.hpp>
#include <Components/BoxCollider2D.hpp>
#include <Components/Transform.hpp>
#include <SFML/Graphics.hpp>

inline bool AABBOverlap(const sf::Vector2f& sizeA, const sf::Vector2f& posA, const sf::Vector2f& sizeB, const sf::Vector2f& posB)
{
    if (posA.x > posB.x + sizeB.x)
        return false;

    if (posA.x + sizeA.x < posB.x)
        return false;

    if (posA.y > posB.y + sizeB.y)
        return false;

    if (posA.y + sizeA.y < posB.y)
        return false;

    return true;
}

inline sf::Vector2f resolveAABB(const sf::Vector2f& sizeA, const sf::Vector2f& posA,
                         const sf::Vector2f& sizeB, const sf::Vector2f& posB)
{
    float dx = (posA.x + sizeA.x / 2) - (posB.x + sizeB.x / 2);
    float dy = (posA.y + sizeA.y / 2) - (posB.y + sizeB.y / 2);
    float overlapX = (sizeA.x + sizeB.x) / 2 - std::abs(dx);
    float overlapY = (sizeA.y + sizeB.y) / 2 - std::abs(dy);

    if (overlapX < 0 || overlapY < 0)
        return {0.f, 0.f}; // No collision

    if (overlapX < overlapY)
        return {dx < 0 ? -overlapX : overlapX, 0.f};
    else
        return {0.f, dy < 0 ? -overlapY : overlapY};
}

class ColliderSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        auto entityList = world.findAll<BoxCollider2D, Transform>();
        for (int i = 0; i < entityList.size(); i++)
        {
            Entity* entityA = entityList[i];
            auto& box1 = entityA->getComponent<BoxCollider2D>();
            auto pos1 = entityA->getComponent<Transform>().getPosition();
            for (int j = i + 1; j < entityList.size(); j++)
            {
                Entity* entityB = entityList[j];
                auto& box2 = entityB->getComponent<BoxCollider2D>();
                auto pos2 = entityB->getComponent<Transform>().getPosition();
                
                if (AABBOverlap(box1.size, box1.offset + pos1, box2.size, box2.offset + pos2))
                {
                    sf::Vector2f mtv = resolveAABB(box1.size, box1.offset + pos1, box2.size, box2.offset + pos2);
                    pos1 += mtv;
                    entityA->getComponent<Transform>().setPosition(pos1);
                }
            }
        }
    }
};