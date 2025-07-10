#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerJumpingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <Components/Animation.hpp>
#include <Components/Input.hpp>
#include <Components/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

void PlayerJumpingState::onEnter(Entity* entity)
{
    if (entity->hasComponent<Animation>())
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/mario_jumping.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 32;
        anim.frameCount = 1;
        anim.frameDuration = 0.0f;
    }
}

std::shared_ptr<PlayerState> PlayerJumpingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<RigidBody>())
    {
        auto& rb = entity->getComponent<RigidBody>();
        if (rb.onGround)
        {
            return std::make_shared<PlayerIdlingState>();
        }
    }

    return nullptr;
}