#include <PlayerPowerStates/PlayerDeadState.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <ECS/Entity.hpp>

const std::string PlayerDeadState::getName() const
{
    return "Dead";
}

void PlayerDeadState::onEnter(Entity* entity)
{   
    entity->removeComponent<InputTag>();
    entity->removeComponent<BoxCollider2D>();
    if (entity->hasComponent<RigidBody>())
    {
        entity->getComponent<RigidBody>().velocity = sf::Vector2f(0, -600);
    }
}

std::shared_ptr<PlayerPowerState> PlayerDeadState::getNewState(Entity* entity)
{
    return nullptr;
}