#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Koopa/KoopaShell_ReviveBehaviour.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaShell_ReviveBehaviour::collideWithPlayer(Entity* entity)
{
    if (!entity->hasComponent<KoopaShellTag>() && !entity->hasComponent<KoopaReviveTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (entity->hasComponent<KoopaShellTag>() || entity->hasComponent<KoopaReviveTag>())
        {
            if (direction == Direction::Left)
            {
                entity->addComponent<ChangeToKoopaSlideTag>();
                entity->getComponent<KoopaPatrol>().lastDirection = Direction::Left;
            }
            else if (direction == Direction::Right)
            {
                entity->addComponent<ChangeToKoopaSlideTag>();
                entity->getComponent<KoopaPatrol>().lastDirection = Direction::Right;
            }
            else if (direction == Direction::Bottom)
            {
                entity->addComponent<ChangeToKoopaSlideTag>();
                
                auto& tfE = entity->getComponent<Transform>();
                auto& tfC = collider->getComponent<Transform>();
                auto cenxE = tfE.position.x + tfE.size.x / 2;
                auto cenxC = tfC.position.x + tfC.size.x / 2;
                
                if (cenxE < cenxC)
                {
                    entity->getComponent<KoopaPatrol>().lastDirection = Direction::Left;
                }
                else if (cenxE > cenxC)
                {
                    entity->getComponent<KoopaPatrol>().lastDirection = Direction::Right;
                }
            }
        }

        break;
    }
}


void KoopaShell_ReviveBehaviour::collideWithOther(Entity* entity)
{
    if (!entity->hasComponent<KoopaShellTag>() && !entity->hasComponent<KoopaReviveTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<KoopaPatrol>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToKoopaFlippedTag>();
        }
    }
}


void KoopaShell_ReviveBehaviour::patrol(Entity* entity, float dt, Entity* camera)
{
    if (!entity->hasComponent<KoopaShellTag>() && !entity->hasComponent<KoopaReviveTag>()) return;
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