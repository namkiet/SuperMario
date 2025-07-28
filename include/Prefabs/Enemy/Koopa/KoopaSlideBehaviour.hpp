#pragma once
#include <Prefabs/Enemy/EnemyBehaviour.hpp>

class KoopaSlideBehaviour : public EnemyBehaviour
{
public:
    ~KoopaSlideBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, Entity* camera) override;
};
