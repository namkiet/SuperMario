#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class GoombaBehaviour : public EnemyBehaviour
{
public:
    ~GoombaBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};


