#include <Gameplay/Player/PlayerMovementStates/PlayerShootingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

PlayerShootingState::PlayerShootingState() : animationTimer(0.125f) {}

const std::string PlayerShootingState::getName() const
{
    return "Shooting";
}

void PlayerShootingState::update(Entity* entity, float dt)
{
    animationTimer -= dt;
}

std::shared_ptr<PlayerMovementState> PlayerShootingState::getNewState(Entity* entity)
{
    if (animationTimer < 0.0f)
    {
        return std::make_shared<PlayerIdlingState>();
    }
    return nullptr;
}