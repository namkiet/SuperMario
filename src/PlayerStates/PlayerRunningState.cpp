#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerJumpingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <Components/Animation.hpp>
#include <Components/Input.hpp>
#include <Components/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

void PlayerRunningState::onEnter(Entity* entity)
{
    if (entity->hasComponent<Animation>())
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/mario_running.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 32;
        anim.frameCount = 3;
        anim.frameDuration = 0.15f;
    }
}

std::shared_ptr<PlayerState> PlayerRunningState::getNewState(Entity* entity)
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