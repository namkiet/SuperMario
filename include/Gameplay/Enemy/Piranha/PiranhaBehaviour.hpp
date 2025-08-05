#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class PiranhaBehaviour : public EnemyBehaviour
{
public:
    ~PiranhaBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};


