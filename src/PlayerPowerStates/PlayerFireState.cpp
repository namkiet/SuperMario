#include <PlayerPowerStates/PlayerFireState.hpp>
#include <PlayerPowerStates/PlayerBigInvincibleState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Fire/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <ECS/Entity.hpp>

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

std::shared_ptr<PlayerPowerState> PlayerFireState::getNewState(Entity* entity)
{
    // if (entity->hasComponent<ShrinkTag>()) 
    // {
    //     return std::make_shared<PlayerShrinkingState>();
    // }
    
    if (entity->hasComponent<InvincibleTag>())
    {
        return std::make_shared<PlayerBigInvincibleState>();
    }

    return nullptr;
}