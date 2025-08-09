#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class BowserJumpBehaviour : public EnemyBehaviour
{
public:
    ~BowserJumpBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
    void attack(Entity* entity, float dt, World& world) override;
};


