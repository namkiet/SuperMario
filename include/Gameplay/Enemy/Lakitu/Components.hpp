#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

enum class PatrolPhase
{
    Chase,
    Oscillate
};

struct ChangeToLakituFlippedTag : public Component {};

struct LakituPatrol : Component
{
    LakituPatrol() {}
    double distance = 150; // The distance to player that Lakitu oscillate back and forth
    float fastSpeed = 500;
    double accelerate;
    PatrolPhase phase = PatrolPhase::Chase;
    sf::Vector2f velocity = sf::Vector2f(-fastSpeed, 0);
    Direction lastDirection = Direction::Left;
    sf::Vector2f freeTarget = sf::Vector2f(500, 0);
    float limitX = 180 * 16 * 3;
};

struct LakituAttack : Component
{
    LakituAttack() {}
    double distance = 300; // The distance to player that Lakitu can attack
    float delay = 5;
    float timer = 0;
};