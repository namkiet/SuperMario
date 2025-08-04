#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

struct BowserBulletPatrol : Component
{
    BowserBulletPatrol() {}
    
    sf::Vector2f velocity = sf::Vector2f(0, 0);
    float targetY;
};