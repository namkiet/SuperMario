#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/EnemyState.hpp>
#include <Prefabs/Enemy/Goomba/Components.hpp>
#include <Prefabs/Enemy/Goomba/GoombaNormalState.hpp>
#include <Prefabs/Enemy/Goomba/GoombaFlippedState.hpp>
#include <Prefabs/Enemy/Goomba/GoombaStompedState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Core/TextureManager.hpp>

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