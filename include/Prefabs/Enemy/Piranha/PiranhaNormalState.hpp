#pragma once
#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/EnemyState.hpp>

class PiranhaNormalState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entit, float dt) override;
};


