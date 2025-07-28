#pragma once
#include <Prefabs/Enemy/EnemyBehaviour.hpp>

class PiranhaBehaviour : public EnemyBehaviour
{
public:
    ~PiranhaBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, Entity* camera) override;
};


