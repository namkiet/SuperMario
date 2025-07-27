#include <PlayerPowerStates/PlayerBigState.hpp>
#include <PlayerPowerStates/PlayerFireState.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/BreakBrick/Components.hpp>
#include <ECS/Entity.hpp>
#include <Core/TextureManager.hpp>

const std::string PlayerBigState::getName() const
{
    return "Big";
}

void PlayerBigState::onEnter(Entity* entity)
{   
    entity->addComponent<CanBreakBrickTag>();
    entity->addComponent<BigMarioTag>();

    if (entity->hasComponent<BoxCollider2D>())
    {
        auto& box = entity->getComponent<BoxCollider2D>();
        box.size.y *= 2.0f;
    }
}

std::shared_ptr<PlayerPowerState> PlayerBigState::getNewState(Entity* entity)
{
    if (entity->hasComponent<FireMarioTag>()) 
    {
        return std::make_shared<PlayerFireState>();
    }

    return nullptr;
}