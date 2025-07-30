#include <PlayerPowerStates/PlayerSmallInvincibleState.hpp>
#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerSmallInvincibleState::getName() const
{
    return "SmallInvincible";
}

std::shared_ptr<PlayerPowerState> PlayerSmallInvincibleState::getNewState(Entity* entity)
{
    if (!entity->hasComponent<InvincibleTag>()) 
    {
        return std::make_shared<PlayerSmallState>();
    }

    return nullptr;
}