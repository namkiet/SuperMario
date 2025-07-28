#pragma once
#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/EnemyState.hpp>

class KoopaFlyingState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) override;
};

