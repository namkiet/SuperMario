#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class SpinyEggBehaviour : public EnemyBehaviour
{
public:
    ~SpinyEggBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};


