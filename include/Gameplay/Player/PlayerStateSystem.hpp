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

            if (tag.powerState->getName() == "GrowingUp" || tag.powerState->getName() == "Dead")
            {
                entity->addComponent<Animation>(getAnimation(tag.powerState->getName()));
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
        animMap["IdlingSmall"] = Animation(TextureManager::load("assets/Mario/Small/idling.png"));
        animMap["JumpingSmall"] = Animation(TextureManager::load("assets/Mario/Small/jumping.png"));
        animMap["RunningSmall"] = Animation(TextureManager::load("assets/Mario/Small/running.png"), 16, 16, 3, 0.15f);
        animMap["IdlingSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/idling_invincible.png"), 16, 16, 4, 0.1f);
        animMap["JumpingSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/jumping_invincible.png"), 16, 16, 4, 0.1f);
        animMap["RunningSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/running_invincible.png"), 16, 16, 12, 0.1f);

        animMap["CrouchingBig"] = Animation(TextureManager::load("assets/Mario/Big/crouching.png"));
        animMap["IdlingBig"] = Animation(TextureManager::load("assets/Mario/Big/idling.png"));
        animMap["JumpingBig"] = Animation(TextureManager::load("assets/Mario/Big/jumping.png"));
        animMap["RunningBig"] = Animation(TextureManager::load("assets/Mario/Big/running.png"), 16, 32, 3, 0.15f);
        animMap["IdlingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/idling_invincible.png"), 16, 32, 4, 0.1f);
        animMap["JumpingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/jumping_invincible.png"), 16, 32, 4, 0.1f);
        animMap["RunningBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/running_invincible.png"), 16, 32, 12, 0.1f);

        animMap["CrouchingFire"] = Animation(TextureManager::load("assets/Mario/Fire/crouching.png"));
        animMap["IdlingFire"] = Animation(TextureManager::load("assets/Mario/Fire/idling.png"));
        animMap["JumpingFire"] = Animation(TextureManager::load("assets/Mario/Fire/jumping.png"));
        animMap["RunningFire"] = Animation(TextureManager::load("assets/Mario/Fire/running.png"), 16, 32, 3, 0.15f);

        animMap["GrowingUp"] = Animation(TextureManager::load("assets/Mario/GrowUp/grow_up.png"), 16, 32, 7, 0.1f, false);
        animMap["Dead"] = Animation(TextureManager::load("assets/Mario/Small/dead.png"));
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