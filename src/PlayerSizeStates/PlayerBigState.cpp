#include <Gameplay/Player/PlayerSizeStates/PlayerBigState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerShrinkingState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerFireState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>

#include <Gameplay/DamageOnContact/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerBigState::getName() const
{
    return "Big";
}

void PlayerBigState::onEnter(Entity* entity)
{   
    entity->addComponent<BigMarioTag>();
}

std::shared_ptr<PlayerSizeState> PlayerBigState::getNewState(Entity* entity)
{
    if (entity->hasComponent<FireMarioTag>()) 
    {
        return std::make_shared<PlayerFireState>();
    }

    if (entity->hasComponent<DamagedTag>())
    {
        return std::make_shared<PlayerShrinkingState>();
    }

    return nullptr;
}