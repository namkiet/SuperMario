#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>

class Entity;

enum class CollisionDirection
{
    None,
    Top,
    Bottom,
    Left,
    Right
};

struct CollisionInfo
{
    Entity* collider = nullptr;
    sf::Vector2f overlap = sf::Vector2f(0, 0);
    CollisionDirection direction = CollisionDirection::None;
};

class BoxCollider2D : public Component
{
public:
    BoxCollider2D(const sf::Vector2f& size = sf::Vector2f(0, 0), const sf::Vector2f& offset = sf::Vector2f(0, 0))
        : size(size), offset(offset) {}

    sf::Vector2f size;
    sf::Vector2f offset;
    bool isSolid = true;     
    bool isTrigger = false;
    CollisionInfo colInfo;
};