#pragma once
#include <Gameplay/Enemy/EnemyBehaviour.hpp>

class KoopaShell_ReviveBehaviour : public EnemyBehaviour
{
public:
    ~KoopaShell_ReviveBehaviour() = default;
    void collideWithPlayer(Entity* entity) override;
    void collideWithOther(Entity* entity) override;
    void patrol(Entity* entity, float dt, Entity* camera) override;
};
