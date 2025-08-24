#pragma once
#include <ECS/System.hpp>
#include <Framework/World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/MessageBus.hpp>
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
        // std::cout << "playerState system works\n";
        for (Entity* player : world.findAll<PlayerTag, Animation>())
        {
            auto& tag = player->getComponent<PlayerTag>();

                        // std::cout << "playerState 0 ok" << std::endl;
            if (!tag.movementState || !tag.sizeState || !tag.powerState) continue;

            tag.movementState->update(player, dt);
            tag.sizeState->update(player, dt);
            tag.powerState->update(player, dt);

            auto newMovementState = tag.movementState->getNewState(player);
            auto newSizeState = tag.sizeState->getNewState(player);
            auto newPowerState = tag.powerState->getNewState(player);
            // std::cout << "playerState 1 ok" << std::endl;

            if (!playerHasChanged && !newMovementState && !newSizeState && !newPowerState) continue;
            std::cout << "change playerState" << std::endl;
            if (playerHasChanged)
            {
                playerHasChanged = false;
                tag.speed = isMario ? 400.0f : 300.0f;
                tag.jumpForce = isMario ? 1100.0f : 1400.0f;
            }

            if (newMovementState)
            {
                
                std::cout << newMovementState->getName() << std::endl;
                
                tag.movementState->onExit(player);
                tag.movementState = newMovementState;
                tag.movementState->onEnter(player);
            }

            if (newSizeState)
            {
                
                std::cout << newSizeState->getName() << std::endl;
                tag.sizeState->onExit(player);
                tag.sizeState = newSizeState;
                tag.sizeState->onEnter(player);
            }
            if (newPowerState)
            {
                std::cout << newPowerState->getName() << std::endl;
                tag.powerState->onExit(player);
                tag.powerState = newPowerState;
                tag.powerState->onEnter(player);
            }

            auto stateName = (isMario ? "Mario" : "Luigi") + tag.movementState->getName() + tag.sizeState->getName() + tag.powerState->getName();
            player->addComponent<Animation>(getAnimation(stateName));
        }
    }

public:
    PlayerStateSystem()
    {
        MessageBus::subscribe("SelectedMario", this, [this](const std::string&) { isMario = true; playerHasChanged = true; });
        MessageBus::subscribe("SelectedLuigi", this, [this](const std::string&) { isMario = false; playerHasChanged = true; });
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

    Animation getAnimation(const std::string& name) const
    {
        auto it = animMap.find(name);
        if (it == animMap.end())
            return Animation();
        return it->second;
    }

    std::unordered_map<std::string, Animation> animMap;
    static inline bool playerHasChanged = false;
    static inline bool isMario = true;
};
