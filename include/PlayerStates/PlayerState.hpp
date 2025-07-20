#pragma once
#include <memory>

class Entity;

class PlayerState
{
public:
    virtual ~PlayerState() = default;
    virtual void onEnter(Entity* entity) = 0;
    virtual std::shared_ptr<PlayerState> getNewState(Entity* entity) = 0;
};