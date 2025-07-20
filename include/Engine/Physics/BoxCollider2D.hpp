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