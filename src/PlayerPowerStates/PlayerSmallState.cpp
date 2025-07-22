#include <PlayerPowerStates/PlayerSmallState.hpp>
#include <PlayerPowerStates/PlayerGrowingUpState.hpp>
#include <Gameplay/Player/Components.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

const std::string PlayerSmallState::getName() const
{
    return "Small";
}

std::shared_ptr<PlayerPowerState> PlayerSmallState::getNewState(Entity* entity)
{
    if (entity->hasComponent<GrowUpTag>()) 
    {
        return std::make_shared<PlayerGrowingUpState>();
    }

    return nullptr;
}