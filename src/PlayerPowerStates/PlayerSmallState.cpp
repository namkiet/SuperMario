#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <PlayerPowerStates/PlayerSmallInvincibleState.hpp>
#include <PlayerPowerStates/PlayerDeadState.hpp>
#include <PlayerPowerStates/PlayerGrowingUpState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerSmallState::getName() const
{
    return "Small";
}

void PlayerSmallState::onEnter(Entity* entity)
{  
    entity->removeComponent<BigMarioTag>();

    // if (entity->hasComponent<Transform>())
    // {
    //     auto& tf = entity->getComponent<Transform>();
    //     tf.size.y *= 0.5f;
    //     tf.position.y += tf.size.y;
    // }

    // if (entity->hasComponent<BoxCollider2D>())
    // {
    //     auto& box = entity->getComponent<BoxCollider2D>();
    //     box.size.y *= 0.5f;
    // }
}

std::shared_ptr<PlayerPowerState> PlayerSmallState::getNewState(Entity* entity)
{
    if (entity->hasComponent<GrowUpTag>()) 
    {
        entity->removeComponent<GrowUpTag>();
        return std::make_shared<PlayerGrowingUpState>();
    }

    if (entity->hasComponent<InvincibleTag>())
    {
        return std::make_shared<PlayerSmallInvincibleState>();
    }

    if (entity->hasComponent<DamagedTag>())
    {
        entity->removeComponent<DamagedTag>();
        return std::make_shared<PlayerDeadState>();
    }

    return nullptr;
}