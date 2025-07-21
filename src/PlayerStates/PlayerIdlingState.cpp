#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerJumpingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

void PlayerIdlingState::onEnter(Entity *entity)
{
    if (entity->hasComponent<Animation>())
    {
        auto &anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Player/SmallPlayer/marioSmall_0.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 28;
        anim.frameCount = 1;
        anim.frameDuration = 0.0f;
    }
}

std::shared_ptr<PlayerState> PlayerIdlingState::getNewState(Entity *entity)
{
    if (entity->hasComponent<RigidBody>())
    {
        auto &rb = entity->getComponent<RigidBody>();
        if (!rb.onGround)
        {
            return std::make_shared<PlayerJumpingState>();
        }

        if (rb.velocity.x != 0.0f)
        {
            return std::make_shared<PlayerRunningState>();
        }
    }

    return nullptr;
}