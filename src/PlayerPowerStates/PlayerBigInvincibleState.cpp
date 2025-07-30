#include <PlayerPowerStates/PlayerBigInvincibleState.hpp>
#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerFireState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerBigInvincibleState::getName() const
{
    return "BigInvincible";
}

std::shared_ptr<PlayerPowerState> PlayerBigInvincibleState::getNewState(Entity* entity)
{
    if (!entity->hasComponent<InvincibleTag>()) 
    {
        if (entity->hasComponent<FireMarioTag>())
        {
            return std::make_shared<PlayerFireState>();
        }
        return std::make_shared<PlayerBigState>();
    }

    return nullptr;
}