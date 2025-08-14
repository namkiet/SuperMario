#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerJumpingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerRunningState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

const std::string PlayerRunningState::getName() const
{
    return "Running";
}

std::shared_ptr<PlayerMovementState> PlayerRunningState::getNewState(Entity* entity)
{
    if (entity->hasComponent<RigidBody>()) 
    {
        auto& rb = entity->getComponent<RigidBody>();
        if (!rb.onGround)
        {
            return std::make_shared<PlayerJumpingState>();
        }

        if (rb.velocity.x == 0.0f)
        {
            return std::make_shared<PlayerIdlingState>();
        }
    }

    return nullptr;
}