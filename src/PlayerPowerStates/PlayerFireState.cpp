#include <PlayerPowerStates/PlayerFireState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Fireball/Components.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

const std::string PlayerFireState::getName() const
{
    return "Fire";
}

void PlayerFireState::onEnter(Entity* entity)
{   
    entity->addComponent<CanShootTag>();
}

void PlayerFireState::onExit(Entity* entity)
{  
    entity->removeComponent<CanShootTag>();
}

std::shared_ptr<PlayerPowerState> PlayerFireState::getNewState(Entity* entity)
{
    // if (entity->hasComponent<ShrinkTag>()) 
    // {
    //     return std::make_shared<PlayerShrinkingState>();
    // }

    return nullptr;
}