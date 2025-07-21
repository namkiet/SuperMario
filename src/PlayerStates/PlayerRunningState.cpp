#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerJumpingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

void PlayerRunningState::onEnter(Entity *entity)
{
    if (entity->hasComponent<Animation>())
    {
        entity->removeComponent<Animation>();

        std::vector<const sf::Texture *> textures = {
            &TextureManager::load("assets/Player/SmallPlayer/marioSmall_1.png"),
            &TextureManager::load("assets/Player/SmallPlayer/marioSmall_2.png"),
            &TextureManager::load("assets/Player/SmallPlayer/marioSmall_3.png")};
        entity->addComponent<Animation>(textures, 48, 48, 0.15f, true);
        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Player/SmallPlayer/marioSmall_1.png"));
        // anim.frameWidth = 16;
        // anim.frameHeight = 32;
        // anim.frameCount = 1;
        // anim.frameDuration = 0.15f;
    }
}

std::shared_ptr<PlayerState> PlayerRunningState::getNewState(Entity *entity)
{
    if (entity->hasComponent<RigidBody>())
    {
        auto &rb = entity->getComponent<RigidBody>();
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