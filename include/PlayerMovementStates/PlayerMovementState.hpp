#pragma once
#include <memory>
#include <string>

class Entity;

class PlayerMovementState
{
public:
    virtual ~PlayerMovementState() = default;
    virtual const std::string getName() const = 0;
    virtual void onEnter(Entity* entity) {}
    virtual void onExit(Entity* entity) {}
    virtual void update(Entity* entity) {}
    virtual std::shared_ptr<PlayerMovementState> getNewState(Entity* entity) = 0;
};