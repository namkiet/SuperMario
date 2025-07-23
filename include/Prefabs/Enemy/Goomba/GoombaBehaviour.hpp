#pragma once
#include <Prefabs/Enemy/EnemyBehaviour.hpp>

class GoombaBehaviour : public EnemyBehaviour
{
public:
    ~GoombaBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void activatePatrol(Entity* entity, Entity* camera) override;
    void patrol(Entity* entity, float dt) override;
};


