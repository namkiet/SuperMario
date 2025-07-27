#pragma once
#include <ECS/System.hpp>
#include <World.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/AnimationManager.hpp>
#include <string>
#include <unordered_map>

class PlayerStateSystem : public System
{
public:
    void update(World& world, float dt) override
    {
        for (Entity* entity : world.findAll<PlayerTag, Animation>())
        {
            auto& tag = entity->getComponent<PlayerTag>();
            auto newMovementState = tag.movementState->getNewState(entity);
            auto newPowerState = tag.powerState->getNewState(entity);

            if (!newMovementState && !newPowerState) continue;

            if (newMovementState)
            {
                tag.movementState->onExit(entity);
                tag.movementState = newMovementState;
                tag.movementState->onEnter(entity);
            }

            if (newPowerState)
            {
                tag.powerState->onExit(entity);
                tag.powerState = newPowerState;
                tag.powerState->onEnter(entity);
            }

            entity->removeComponent<Animation>();

            if (tag.powerState->getName() == "GrowingUp")
            {
                entity->addComponent<Animation>(getAnimation("GrowingUp"));
            }
            else
            {
                entity->addComponent<Animation>(getAnimation(tag.movementState->getName() + tag.powerState->getName()));
            }
        }
    }

public:
    PlayerStateSystem()
    {
        animMap["IdlingSmall"] = Animation(TextureManager::load("assets/Mario/Small/mario_idling_small.png"));
        animMap["JumpingSmall"] = Animation(TextureManager::load("assets/Mario/Small/mario_jumping_small.png"));
        animMap["RunningSmall"] = Animation(TextureManager::load("assets/Mario/Small/mario_running_small.png"), 16, 16, 3, 0.15f);

        animMap["IdlingBig"] = Animation(TextureManager::load("assets/Mario/Big/mario_idling_big.png"));
        animMap["JumpingBig"] = Animation(TextureManager::load("assets/Mario/Big/mario_jumping_big.png"));
        animMap["RunningBig"] = Animation(TextureManager::load("assets/Mario/Big/mario_running_big.png"), 16, 32, 3, 0.15f);

        animMap["IdlingFire"] = Animation(TextureManager::load("assets/Mario/Fire/mario_idling_fire.png"));
        animMap["JumpingFire"] = Animation(TextureManager::load("assets/Mario/Fire/mario_jumping_fire.png"));
        animMap["RunningFire"] = Animation(TextureManager::load("assets/Mario/Fire/mario_running_fire.png"), 16, 32, 3, 0.15f);

        animMap["GrowingUp"] = Animation(TextureManager::load("assets/Mario/GrowUp/mario_grow_up.png"), 16, 32, 7, 0.1f, false);
    }

private:
    Animation getAnimation(const std::string& name) const
    {
        if (animMap.find(name) == animMap.end())
        {
            throw std::runtime_error("Cannot find Animation: " + name);
        }

        return animMap.at(name);
    }
    std::unordered_map<std::string, Animation> animMap;
};