#pragma once
#include <Engine/Camera/Camera.hpp>

class Entity;
class World;

class EnemyBehaviour
{
public:
    virtual ~EnemyBehaviour() = default;
    virtual void collideWithPlayer(Entity* entity) = 0;
    virtual void collideWithOther(Entity* entity) = 0; // Collide with other enemy and block
    virtual void patrol(Entity* entity, float dt, World& world) = 0;
    virtual void attack(Entity* entity, float dt, World& world) {} // Some enemies can actively attack
};