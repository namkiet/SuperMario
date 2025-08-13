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

            auto stateName = tag.movementState->getName() + tag.sizeState->getName() + tag.powerState->getName();
            player->addComponent<Animation>(getAnimation(stateName));
        }
    }

public:
    PlayerStateSystem()
    {
        animMap["IdlingSmallNormal"] = Animation(TextureManager::load("assets/Mario/Small/idling.png"));
        animMap["IdlingSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/idling_invincible.png"), 16, 16, 4, 0.1f);
        animMap["IdlingBigNormal"] = Animation(TextureManager::load("assets/Mario/Big/idling.png"));
        animMap["IdlingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/idling_invincible.png"), 16, 32, 4, 0.1f);
        animMap["IdlingFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/idling.png"));
        animMap["IdlingFireInvincible"] = animMap["IdlingBigInvincible"];
        animMap["IdlingDeadNormal"] = Animation(TextureManager::load("assets/Mario/Small/dead.png"));
        animMap["IdlingDeadInvincible"] = Animation();
        animMap["IdlingShrinkingNormal"] = Animation(TextureManager::load("assets/Mario/Big/shrinking.png"), 16, 32, 10, 0.1f, false);
        // animMap["IdlingShrinkingInvincible"] = Animation(TextureManager::load("assets/Mario/Big/shrinking.png"), 16, 32, 10, 0.1f, false);
        animMap["IdlingGrowingUpNormal"] = Animation(TextureManager::load("assets/Mario/Small/grow_up.png"), 16, 32, 7, 0.1f, false);
        // animMap["IdlingGrowingUpInvincible"] = Animation(TextureManager::load("assets/Mario/Small/grow_up.png"), 16, 32, 7, 0.1f, false);

        animMap["JumpingSmallNormal"] = Animation(TextureManager::load("assets/Mario/Small/jumping.png"));
        animMap["JumpingSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/jumping_invincible.png"), 16, 16, 4, 0.1f);
        animMap["JumpingBigNormal"] = Animation(TextureManager::load("assets/Mario/Big/jumping.png"));
        animMap["JumpingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/jumping_invincible.png"), 16, 32, 4, 0.1f);
        animMap["JumpingFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/jumping.png"));
        animMap["JumpingFireInvincible"] = animMap["JumpingBigInvincible"];
        animMap["JumpingDeadNormal"] = animMap["IdlingDeadNormal"];
        animMap["JumpingDeadInvincible"] = animMap["IdlingDeadInvincible"];
        animMap["JumpingShrinkingNormal"] = animMap["IdlingShrinkingNormal"];
        animMap["JumpingShrinkingInvincible"] = animMap["IdlingShrinkingInvincible"];
        animMap["JumpingGrowingUpNormal"] = animMap["IdlingGrowingUpNormal"];
        animMap["JumpingGrowingUpInvincible"] = animMap["IdlingGrowingUpInvincible"];

        animMap["RunningSmallNormal"] = Animation(TextureManager::load("assets/Mario/Small/running.png"), 16, 16, 3, 0.15f);
        animMap["RunningSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/running_invincible.png"), 16, 16, 12, 0.1f);
        animMap["RunningBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/running_invincible.png"), 16, 32, 12, 0.1f);
        animMap["RunningBigNormal"] = Animation(TextureManager::load("assets/Mario/Big/running.png"), 16, 32, 3, 0.15f);
        animMap["RunningFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/running.png"), 16, 32, 3, 0.15f);
        animMap["RunningFireInvincible"] = animMap["RunningBigInvincible"];
        animMap["RunningDeadNormal"] = animMap["IdlingDeadNormal"];
        animMap["RunningDeadInvincible"] = animMap["IdlingDeadInvincible"];
        animMap["RunningShrinkingNormal"] = animMap["IdlingShrinkingNormal"];
        animMap["RunningShrinkingInvincible"] = animMap["IdlingShrinkingInvincible"];
        animMap["RunningGrowingUpNormal"] = animMap["IdlingGrowingUpNormal"];
        animMap["RunningGrowingUpInvincible"] = animMap["IdlingGrowingUpInvincible"];

        animMap["ClimbingSmallNormal"] = Animation(TextureManager::load("assets/Mario/Small/climbing.png"), 16, 16, 2, 0.2f);
        animMap["ClimbingSmallInvincible"] = Animation(TextureManager::load("assets/Mario/Small/climbing_invincible.png"), 16, 16, 4, 0.2f);
        animMap["ClimbingBigNormal"] = Animation(TextureManager::load("assets/Mario/Big/climbing.png"), 16, 32, 2, 0.2f);
        animMap["ClimbingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/climbing_invincible.png"), 16, 32, 4, 0.2f);
        animMap["ClimbingFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/climbing.png"), 16, 32, 2, 0.2f);
        animMap["ClimbingFireInvincible"] = animMap["ClimbingBigInvincible"];
        animMap["ClimbingDeadNormal"] = animMap["IdlingDeadNormal"];
        animMap["ClimbingDeadInvincible"] = animMap["IdlingDeadInvincible"];
        animMap["ClimbingShrinkingNormal"] = animMap["IdlingShrinkingNormal"];
        animMap["ClimbingShrinkingInvincible"] = animMap["IdlingShrinkingInvincible"];
        animMap["ClimbingGrowingUpNormal"] = animMap["IdlingGrowingUpNormal"];
        animMap["ClimbingGrowingUpInvincible"] = animMap["IdlingGrowingUpInvincible"];

        animMap["CrouchingSmallNormal"] = Animation();
        animMap["CrouchingSmallInvincible"] = Animation();
        animMap["CrouchingBigNormal"] = Animation(TextureManager::load("assets/Mario/Big/crouching.png"));
        // animMap["CrouchingBigInvincible"] = Animation(TextureManager::load("assets/Mario/Big/crouching.png"));
        animMap["CrouchingFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/crouching.png"));
        animMap["CrouchingFireInvincible"] = animMap["CrouchingBigInvincible"];animMap["ClimbingDeadNormal"] = animMap["IdlingDeadNormal"];
        animMap["CroochingDeadNormal"] = animMap["IdlingDeadNormal"];
        animMap["CrouchingDeadInvincible"] = animMap["IdlingDeadInvincible"];
        animMap["CrouchingShrinkingNormal"] = animMap["IdlingShrinkingNormal"];
        animMap["CrouchingShrinkingInvincible"] = animMap["IdlingShrinkingInvincible"];
        animMap["CrouchingGrowingUpNormal"] = animMap["IdlingGrowingUpNormal"];
        animMap["CrouchingGrowingUpInvincible"] = animMap["IdlingGrowingUpInvincible"];

        animMap["ShootingFireNormal"] = Animation(TextureManager::load("assets/Mario/Fire/shooting.png"));
        animMap["ShootingFireInvincible"] = animMap["ShootingFireNormal"];
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
    std::vector<std::string> specialStates;
};