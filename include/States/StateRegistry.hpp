// === StateRegistry.hpp ===
#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "GameState.hpp"

class StateRegistry
{
public:
    void registerInstance(const std::string& name, std::shared_ptr<GameState> instance) 
    {
        states[name] = instance;
    }

    std::shared_ptr<GameState> getState(const std::string& name) const
    {
        auto it = states.find(name);
        return (it != states.end()) ? it->second : nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<GameState>> states;
};