#include <World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Spiny/Components.hpp>
#include <Gameplay/Enemy/Spiny/SpinyNormalBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>

void SpinyNormalBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}

void SpinyNormalBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<SpinyPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToSpinyFlippedTag>();
        }
        else if (direction == Direction::Left && patrol.velocity.x > 0)
        {
            patrol.velocity.x *= -1;
        }
        else if (direction == Direction::Right && patrol.velocity.x < 0)
        {
            patrol.velocity.x *= -1;
        }
    }
}


void SpinyNormalBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<SpinyPatrol>()) return;

    auto& patrol = entity->getComponent<SpinyPatrol>();
    auto& rb = entity->getComponent<RigidBody>();

    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (rb.velocity.y != 0)
    {
        rb.velocity.y += -1200 * dt;
    }
}