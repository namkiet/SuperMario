#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerBigInvincibleState.hpp>
#include <PlayerPowerStates/PlayerFireState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>
#include <Gameplay/Invincible/Components.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerBigState::getName() const
{
    return "Big";
}

void PlayerBigState::onEnter(Entity* entity)
{   
    entity->addComponent<CanBreakBrickTag>();
    entity->addComponent<BigMarioTag>();
}

std::shared_ptr<PlayerPowerState> PlayerBigState::getNewState(Entity* entity)
{
    if (entity->hasComponent<FireMarioTag>()) 
    {
        return std::make_shared<PlayerFireState>();
    }

    if (entity->hasComponent<InvincibleTag>())
    {
        return std::make_shared<PlayerBigInvincibleState>();
    }

    return nullptr;
}