#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <vector>

#include <iostream>

class Entity;

enum class Direction
{
    None,
    Top,
    Bottom,
    Left,
    Right
};

struct CollisionInfo
{
    CollisionInfo(Entity* collider = nullptr, Direction direction = Direction::None)
        : collider(collider), direction(direction) {}
        
    Entity* collider;
    Direction direction;
};

class BoxCollider2D : public Component
{
public:
    BoxCollider2D(const sf::Vector2f& size = sf::Vector2f(0, 0), const sf::Vector2f& offset = sf::Vector2f(0, 0))
        : size(size), offset(offset) {}

    sf::Vector2f size;
    sf::Vector2f offset;
    bool isTrigger = false;
    std::vector<CollisionInfo> collisions;
};

inline std::ostream& operator<<(std::ostream& os, Direction dir) {
    switch (dir) {
        case Direction::None:   return os << "None";
        case Direction::Top:    return os << "Top";
        case Direction::Bottom: return os << "Bottom";
        case Direction::Left:   return os << "Left";
        case Direction::Right:  return os << "Right";
        default:                         return os << "Unknown";
    }
}