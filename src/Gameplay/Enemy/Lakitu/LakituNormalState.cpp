#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/EnemyState.hpp>
#include <Gameplay/Enemy/Lakitu/Components.hpp>
#include <Gameplay/Enemy/Lakitu/LakituNormalState.hpp>
#include <Gameplay/Enemy/Lakitu/LakituFlippedState.hpp>
#include <Engine/Animation/Animation.hpp>

void LakituNormalState::onEnter(Entity* entity)
{
    // no-op
}

std::shared_ptr<EnemyState> LakituNormalState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToLakituFlippedTag>())
    {
        entity->removeComponent<ChangeToLakituFlippedTag>();
        return std::make_shared<LakituFlippedState>();
    }

    return nullptr;
}