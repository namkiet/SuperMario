#pragma once
#include <ECS/Component.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Entity;

enum class Direction
{
    None,
    Top,
    Bottom,
    Left,
    Right
};

inline Direction opposite(Direction dir)
{
    switch (dir)
    {
        case Direction::Top: 
            return Direction::Bottom;
        
        case Direction::Bottom: 
            return Direction::Top;
        
        case Direction::Left: 
            return Direction::Right;
        
        case Direction::Right: 
            return Direction::Left;
        
        default: 
            return Direction::None;
    }
}

struct CollisionInfo
{
    CollisionInfo(Entity* collider = nullptr, Direction direction = Direction::None, sf::FloatRect overlap = sf::FloatRect())
        : collider(collider), direction(direction), overlap(overlap) {}
        
    Entity* collider;
    Direction direction;
    sf::FloatRect overlap;
};

class BoxCollider2D : public Component
{
public:
    BoxCollider2D(const sf::Vector2f& size = sf::Vector2f(0, 0), const sf::Vector2f& offset = sf::Vector2f(0, 0), bool bounce = false)
        : size(size), offset(offset), bounce(bounce), isDisabled(false) {}
    bool isDisabled;
    sf::Vector2f size;
    sf::Vector2f offset;
    bool bounce = false;
    std::vector<CollisionInfo> collisions;
};