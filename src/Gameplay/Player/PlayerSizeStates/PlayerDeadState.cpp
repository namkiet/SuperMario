#include <Gameplay/Player/PlayerSizeStates/PlayerDeadState.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Entity/Entity.hpp>

#include <Engine/Audio/SoundManager.hpp>

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
    entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/death.wav"), false);
}

std::shared_ptr<PlayerSizeState> PlayerDeadState::getNewState(Entity* entity)
{
    return nullptr;
}