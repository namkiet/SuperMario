#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyEggState.hpp>
#include <Gameplay/Enemy/Spiny/SpinyNormalState.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Gameplay/DamageOnContact/Components.hpp>
#include <Gameplay/Stomp/Components.hpp>

void SpinyEggState::onEnter(Entity* entity)
{
    // no-op
}

std::shared_ptr<EnemyState> SpinyEggState::getNewState(Entity* entity, float dt)
{
    if (entity->hasComponent<ChangeToSpinyNormalTag>())
    {
        entity->removeComponent<ChangeToSpinyNormalTag>();
        return std::make_shared<SpinyNormalState>();
    }

    return nullptr;
}