#pragma once
#include <Prefabs/Enemy/EnemyBehaviour.hpp>

class KoopaFlyingBehaviour : public EnemyBehaviour
{
public:
    ~KoopaFlyingBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, Entity* camera) override;
};
