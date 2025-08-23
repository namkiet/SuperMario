#include <Gameplay/Player/PlayerMovementStates/PlayerShootingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Entity/Entity.hpp>
#include <Core/TextureManager.hpp>

PlayerShootingState::PlayerShootingState() : animationDuration(0.125f) {}

const std::string PlayerShootingState::getName() const
{
    return "Shooting";
}

void PlayerShootingState::update(Entity* entity, float dt)
{
    animationDuration -= dt;
}

std::shared_ptr<PlayerMovementState> PlayerShootingState::getNewState(Entity* entity)
{
    if (animationDuration < 0.0f)
    {
        return std::make_shared<PlayerIdlingState>();
    }
    return nullptr;
}