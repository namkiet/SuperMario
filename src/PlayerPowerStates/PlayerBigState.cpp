#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <PlayerPowerStates/PlayerGrowingUpState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

const std::string PlayerBigState::getName() const
{
    return "Big";
}

void PlayerBigState::onEnter(Entity* entity)
{   
    entity->addComponent<CanBreakBrickTag>();
    entity->addComponent<BigMarioTag>();

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 2.0f;
    }
}

void PlayerBigState::onExit(Entity* entity)
{  
    entity->removeComponent<CanBreakBrickTag>();
    entity->removeComponent<BigMarioTag>();

    if (entity->hasComponent<Transform>())
    {
        auto& tf = entity->getComponent<Transform>();
        tf.size.y *= 0.5f;
        tf.position.y += tf.size.y;
    }

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 0.5f;
    }
}

std::shared_ptr<PlayerPowerState> PlayerBigState::getNewState(Entity* entity)
{
    // if (!entity->hasComponent<ShrinkTag>()) 
    // {
    //     return std::make_shared<PlayerShrinkingState>();
    // }

    return nullptr;
}