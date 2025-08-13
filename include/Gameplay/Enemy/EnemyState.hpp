#pragma once
#include <memory>
#include <Factories/EnemyFactory.hpp>

class Entity;

class EnemyState
{
public:
    virtual ~EnemyState() = default;
    virtual void onEnter(Entity* entity) = 0;
    virtual std::shared_ptr<EnemyState> getNewState(Entity* entity, float dt) = 0;
};