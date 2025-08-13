#include <Gameplay/Player/PlayerSizeStates/PlayerSmallState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerDeadState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerGrowingUpState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Animation/BlinkingComponent.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>

#include <ECS/Entity.hpp>

const std::string PlayerSmallState::getName() const
{
    return "Small";
}

void PlayerSmallState::onEnter(Entity* entity)
{  
    entity->removeComponent<CanBreakBrickTag>();
    entity->removeComponent<BigMarioTag>();
}

void PlayerSmallState::update(Entity* entity, float dt)
{
    if (!entity->hasComponent<BlinkingComponent>() && !entity->hasComponent<InvincibleTag>())
    {
        entity->addComponent<CanGetDamageTag>();
    }
}

std::shared_ptr<PlayerSizeState> PlayerSmallState::getNewState(Entity* entity)
{
    if (entity->hasComponent<GrowUpTag>()) 
    {
        return std::make_shared<PlayerGrowingUpState>();
    }

    if (entity->hasComponent<DamagedTag>()) 
    {
        return std::make_shared<PlayerDeadState>();
    }

    return nullptr;
}