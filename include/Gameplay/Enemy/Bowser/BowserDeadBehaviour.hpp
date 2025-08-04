#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class BowserDeadBehaviour : public EnemyBehaviour
{
public:
    ~BowserDeadBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};


