#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class BowserIdleBehaviour : public EnemyBehaviour
{
public:
    ~BowserIdleBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
    void attack(Entity* entity, float dt, World& world) override;
};


