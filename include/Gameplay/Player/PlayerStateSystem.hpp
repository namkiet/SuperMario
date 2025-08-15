#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/AnimationManager.hpp>
#include <string>
#include <unordered_map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class PlayerStateSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* player : world.findAll<PlayerTag, Animation>())
        {
            auto& tag = player->getComponent<PlayerTag>();
            tag.movementState->update(player, dt);
            tag.sizeState->update(player, dt);
            tag.powerState->update(player, dt);

            auto newMovementState = tag.movementState->getNewState(player);
            auto newSizeState = tag.sizeState->getNewState(player);
            auto newPowerState = tag.powerState->getNewState(player);

            if (!newMovementState && !newSizeState && !newPowerState) continue;

            if (newMovementState)
            {
                tag.movementState->onExit(player);
                tag.movementState = newMovementState;
                tag.movementState->onEnter(player);
            }

            if (newSizeState)
            {
                tag.sizeState->onExit(player);
                tag.sizeState = newSizeState;
                tag.sizeState->onEnter(player);
            }

            if (newPowerState)
            {
                tag.powerState->onExit(player);
                tag.powerState = newPowerState;
                tag.powerState->onEnter(player);
            }

            auto stateName = "Luigi"+ tag.movementState->getName() + tag.sizeState->getName() + tag.powerState->getName();
            player->addComponent<Animation>(getAnimation(stateName));
        }
    }

public:
    PlayerStateSystem()
    {
        loadAnimationsFromFile("assets/Player/player_animation.json");
    }

private:
    void loadAnimationsFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open()) throw std::runtime_error("Cannot open JSON file: " + filename);

        json j; fin >> j;
        loadAnimationsFromJSON(j["Mario"], "Mario");
        loadAnimationsFromJSON(j["Luigi"], "Luigi");
    }

    void loadAnimationsFromJSON(const json& j, const std::string& character)
    {
        for (auto& anim : j["animations"])
        {
            std::string key = character + anim["key"].get<std::string>();
            std::string path = anim["path"].get<std::string>();
            int frameWidth = anim.value("frameWidth", 16);
            int frameHeight = anim.value("frameHeight", 16);
            int frameCount = anim.value("frameCount", 1);
            float frameTime = anim.value("frameTime", 0.1f);
            bool loop = anim.value("loop", true);

            animMap[key] = Animation(TextureManager::load(path), frameWidth, frameHeight, frameCount, frameTime, loop);
        }

        for (auto& [alias, original] : j["aliases"].items())
        {
            animMap[character + alias] = animMap.at(character + original.get<std::string>());
        }
    }

    const Animation& getAnimation(const std::string& name) const
    {
        auto it = animMap.find(name);
        if (it == animMap.end())
            throw std::runtime_error("Cannot find Animation: " + name);
        return it->second;
    }

    std::unordered_map<std::string, Animation> animMap;
};
