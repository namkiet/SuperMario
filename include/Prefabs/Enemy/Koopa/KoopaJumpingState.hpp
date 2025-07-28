#pragma once
#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/EnemyState.hpp>

class KoopaJumpingState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) override;
};

