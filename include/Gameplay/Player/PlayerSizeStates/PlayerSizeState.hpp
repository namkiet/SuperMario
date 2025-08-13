#pragma once
#include <memory>
#include <string>

class Entity;

class PlayerSizeState
{
public:
    virtual ~PlayerSizeState() = default;
    virtual const std::string getName() const = 0;
    virtual void onEnter(Entity* entity) {}
    virtual void onExit(Entity* entity) {}
    virtual void update(Entity* entity, float dt) {}
    virtual std::shared_ptr<PlayerSizeState> getNewState(Entity* entity) = 0;
};