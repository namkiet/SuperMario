#include <Framework/World.hpp>
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyEggBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>

void SpinyEggBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}

void SpinyEggBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<SpinyPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToSpinyFlippedTag>();
        }
        else if (direction == Direction::Top)
        {
            entity->addComponent<ChangeToSpinyNormalTag>();
            entity->getComponent<RigidBody>().velocity.y = -200;
        }
    }
}

void SpinyEggBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<SpinyPatrol>()) return;

    auto& patrol = entity->getComponent<SpinyPatrol>();
    auto& rb = entity->getComponent<RigidBody>();

    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}