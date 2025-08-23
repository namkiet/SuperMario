#include <Gameplay/Player/PlayerSizeStates/PlayerFireState.hpp>
#include <Gameplay/Player/PlayerSizeStates/PlayerShrinkingState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Fire/Components.hpp>

#include <Gameplay/DamageOnContact/Components.hpp>
#include <Entity/Entity.hpp>

const std::string PlayerFireState::getName() const
{
    return "Fire";
}

void PlayerFireState::onEnter(Entity* entity)
{   
    entity->addComponent<CanFireTag>();
}

void PlayerFireState::onExit(Entity* entity)
{  
    entity->removeComponent<CanFireTag>();
}

std::shared_ptr<PlayerSizeState> PlayerFireState::getNewState(Entity* entity)
{
    if (entity->hasComponent<DamagedTag>())
    {
        return std::make_shared<PlayerShrinkingState>();
    }

    return nullptr;
}