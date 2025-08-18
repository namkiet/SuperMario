#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaNormalState.hpp>
#include <Gameplay/Enemy/Goomba/GoombaFlippedState.hpp>
#include <Gameplay/Enemy/Goomba/GoombaStompedState.hpp>
#include <Engine/Animation/Animation.hpp>

void GoombaNormalState::onEnter(Entity* entity)
{
    // no-op
}

std::shared_ptr<EnemyState> GoombaNormalState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToGoombaFlippedTag>())
    {
        entity->removeComponent<ChangeToGoombaFlippedTag>();
        return std::make_shared<GoombaFlippedState>();
    }

    if (entity->hasComponent<ChangeToGoombaStompedTag>())
    {
        entity->removeComponent<ChangeToGoombaStompedTag>();
        return std::make_shared<GoombaStompedState>();
    }

    return nullptr;
}