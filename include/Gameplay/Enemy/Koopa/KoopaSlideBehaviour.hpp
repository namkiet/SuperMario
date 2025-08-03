#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class World;

class KoopaSlideBehaviour : public EnemyBehaviour
{
public:
    ~KoopaSlideBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, World& world) override;
};
