#pragma once
#include <memory>
#include <string>

class Entity;

class PlayerPowerState
{
public:
    virtual ~PlayerPowerState() = default;
    virtual const std::string getName() const = 0;
    virtual void onEnter(Entity* entity) {}
    virtual void onExit(Entity* entity) {}
    virtual void update(Entity* entity, float dt) {}
    virtual std::shared_ptr<PlayerPowerState> getNewState(Entity* entity) = 0;
};