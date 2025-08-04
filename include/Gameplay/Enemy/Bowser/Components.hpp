#pragma once
#include <SFML/Graphics.hpp>
#include <ECS/Component.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>

struct ChangeToBowserIdleTag : public Component {};
struct ChangeToBowserWalkTag : public Component {};
struct ChangeToBowserJumpTag : public Component {};
struct ChangeToBowserHurtTag : public Component {};
struct ChangeToBowserSkidTag : public Component {};
struct ChangeToBowserSlideTag : public Component {};
struct ChangeToBowserDeadTag : public Component {};


struct BowserPatrol : Component
{
    BowserPatrol() {}
    double safeDist = 150;
    float duration = 5; // Duration of moving away from player
    float timerDura = 0;
    float jumpCooldown = 5; // Cooldown of jumping when moving toward player
    float timerJump = 0;
    
    sf::Vector2f velocity = sf::Vector2f(0, 0);
    sf::Vector2f accelerate = sf::Vector2f(0, 0);
    Direction lastDirection = Direction::Left;
};


struct BowserAttack : Component
{
    BowserAttack() {}
    double distance = 1000; // The distance to player that Bowser can attack
    float delay = 4;
    float timer = 0;
    float castTime = 0;
    bool isShooting = 0;
};


struct StateDuration : Component
{
    StateDuration(float duration = 0) : duration(duration) {}
    float duration = 0;
    float timer = 0;
};