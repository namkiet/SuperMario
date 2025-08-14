#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Koopa/KoopaSlideBehaviour.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaSlideBehaviour::collideWithPlayer(Entity* entity)
{   
    if (!entity->hasComponent<KoopaSlideTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
        if (collider->hasComponent<PlayerTag>())
        {
            if (collider->hasComponent<CanKillEnemyTag>())
            {
                entity->addComponent<ChangeToKoopaFlippedTag>();
            }
            else if (direction == Direction::Bottom)
            {
                entity->addComponent<ChangeToKoopaShellTag>();
            }
            break;
        }
}


void KoopaSlideBehaviour::collideWithOther(Entity* entity)
{
    if (!entity->hasComponent<KoopaSlideTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<KoopaPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<EnemyTag>()) continue;
        if (collider->hasComponent<PlayerTag>()) continue;

        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToKoopaFlippedTag>();
        }

        if (direction == Direction::Left && patrol.lastDirection == Direction::Right && patrol.velocity.x != 0)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Left;
        }
        else if (direction == Direction::Right && patrol.lastDirection == Direction::Left && patrol.velocity.x != 0)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Right;
        }
    }
}


void KoopaSlideBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<KoopaSlideTag>()) return;
    if (!entity->hasComponent<KoopaPatrol>()) return;

    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& rb = entity->getComponent<RigidBody>();
    
    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}