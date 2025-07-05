#include <PlayerStates/PlayerIdlingState.hpp>
#include <PlayerStates/PlayerJumpingState.hpp>
#include <PlayerStates/PlayerRunningState.hpp>
#include <Components/Animation.hpp>
#include <Components/Input.hpp>
#include <Components/RigidBody.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>
#include <iostream>

void PlayerIdlingState::onEnter(Entity* entity)
{   
    if (entity->hasComponent<Animation>()) 
    {
        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/mario_idling.png"));
        anim.frameWidth = 16;
        anim.frameHeight = 28;
        anim.frameCount = 1;
        anim.frameDuration = 0.0f;
    }
}

std::shared_ptr<PlayerState> PlayerIdlingState::getNewState(Entity* entity)
{
    if (entity->hasComponent<RigidBody>()) 
    {
        auto& rb = entity->getComponent<RigidBody>();
        if (!rb.onGround)
        {
            return std::make_shared<PlayerJumpingState>();
        }
    }

    if (entity->hasComponent<Input>()) 
    {
        auto& input = entity->getComponent<Input>();
        if (input.moveLeft || input.moveRight)
        {
            std::cout << "HELLo\n";
            return std::make_shared<PlayerRunningState>();
        }
    }

    return nullptr;
}