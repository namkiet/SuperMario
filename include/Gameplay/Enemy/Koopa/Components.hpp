#pragma once
#include <ECS/Component.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

struct KoopaTag : public Component {};
struct KoopaNormalTag : public Component {};
struct KoopaFlippedTag : public Component {};
struct KoopaShellTag : public Component {};
struct KoopaReviveTag : public Component {};
struct KoopaSlideTag : public Component {};
struct KoopaJumpingTag : public Component {};
struct KoopaFlyingTag : public Component {};
struct ChangeToKoopaNormalTag : public Component {};
struct ChangeToKoopaFlippedTag : public Component {};
struct ChangeToKoopaShellTag : public Component {};
struct ChangeToKoopaReviveTag : public Component {};
struct ChangeToKoopaSlideTag : public Component {};

struct KoopaPatrol : public Component
{
    KoopaPatrol() : velocity(sf::Vector2f(0, 0)), lastDirection(Direction::None) {}
    KoopaPatrol(sf::Vector2f velocity, Direction lastDirection) : velocity(velocity), lastDirection(lastDirection) {}
    
    sf::Vector2f velocity;
    Direction lastDirection;
};

struct KoopaFlyingPatrol : public Component
{
    KoopaFlyingPatrol() : velocity(sf::Vector2f(0, 0)) {}
    
    sf::Vector2f velocity;
    float phaseDuration = 3;
    float timer = 0;
};