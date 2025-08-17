#pragma once
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>

class KoopaShellState : public EnemyState
{
public:
    void onEnter(Entity* entity) override;
    std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) override;

private:
    float timer = 0.0f;
    float stateDuration = 7.0f;
};


