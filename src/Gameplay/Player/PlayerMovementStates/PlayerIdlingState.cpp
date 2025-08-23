#include <Gameplay/Player/PlayerMovementStates/PlayerIdlingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerJumpingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerRunningState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerShootingState.hpp>
#include <Gameplay/Player/PlayerMovementStates/PlayerCrouchingState.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Entity/Entity.hpp>
#include <Core/TextureManager.hpp>
#include <Core/KeyPressPool.hpp>

const std::string PlayerIdlingState::getName() const
{
    return "Idling";
}

std::shared_ptr<PlayerMovementState> PlayerIdlingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<RigidBody>()) 
    {
        auto& rb = entity->getComponent<RigidBody>();
        if (!rb.onGround)
        {
            return std::make_shared<PlayerJumpingState>();
        }
        else if (entity->hasComponent<BigMarioTag>() && KeyPressPool::Instance().isKeyPressed(sf::Keyboard::S)) 
        {
            return std::make_shared<PlayerCrouchingState>();
        }

        if (rb.velocity.x != 0.0f)
        {
            return std::make_shared<PlayerRunningState>();
        }
    }
    
    if (entity->hasComponent<ShootingTag>())
    {
        return std::make_shared<PlayerShootingState>();
    }

    return nullptr;
}