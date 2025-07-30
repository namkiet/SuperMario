#pragma once
#include <memory>

class Entity;

class EnemyState
{
public:
    virtual ~EnemyState() = default;
    virtual void onEnter(Entity* entity) = 0;
    virtual std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) = 0;
};