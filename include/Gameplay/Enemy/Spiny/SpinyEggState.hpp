#pragma once
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>

class SpinyEggState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entit, float dt) override;
};


