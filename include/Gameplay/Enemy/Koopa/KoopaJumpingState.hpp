#pragma once
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>

class KoopaJumpingState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) override;
};

