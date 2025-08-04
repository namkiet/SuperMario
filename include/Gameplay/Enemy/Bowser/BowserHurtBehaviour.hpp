#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class BowserHurtBehaviour : public EnemyBehaviour
{
public:
    ~BowserHurtBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};


