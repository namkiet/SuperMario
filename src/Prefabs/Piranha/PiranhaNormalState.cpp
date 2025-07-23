#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Piranha/PiranhaNormalState.hpp>

void PiranhaNormalState::onEnter(Entity* entity)
{
    // no-op
}

std::shared_ptr<EnemyState> PiranhaNormalState::getNewState(Entity* entity, float dt)
{
    return nullptr;
}