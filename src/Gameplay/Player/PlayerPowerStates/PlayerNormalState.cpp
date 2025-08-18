#include <Gameplay/Player/PlayerPowerStates/PlayerNormalState.hpp>
#include <Gameplay/Player/PlayerPowerStates/PlayerInvincibleState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerNormalState::getName() const
{
    return "Normal";
}

std::shared_ptr<PlayerPowerState> PlayerNormalState::getNewState(Entity* player)
{
    if (player->hasComponent<InvincibleTag>()) 
    {
        return std::make_shared<PlayerInvincibleState>();
    }

    return nullptr;
}