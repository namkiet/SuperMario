#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class LakituNormalBehaviour : public EnemyBehaviour
{
public:
    ~LakituNormalBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
    void attack(Entity* entity, float dt, World& world) override;
};


