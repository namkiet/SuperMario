#include <Framework/World.hpp>
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumpingBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaJumpingBehaviour::collideWithPlayer(Entity* entity)
{
    if (!entity->hasComponent<KoopaJumpingTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToKoopaFlippedTag>();
        }
        else if (direction == Direction::Bottom)
        {
            entity->addComponent<ChangeToKoopaNormalTag>();
            entity->getComponent<RigidBody>().velocity.y += 500;
        }
        break;
    }
}


void KoopaJumpingBehaviour::collideWithOther(Entity* entity)
{
    if (!entity->hasComponent<KoopaJumpingTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<KoopaPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
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


void KoopaJumpingBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<KoopaJumpingTag>()) return;
    if (!entity->hasComponent<KoopaPatrol>()) return;

    auto& cam = world.findFirst<Camera>()->getComponent<Camera>();
    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();

    // Koopa starts patrolling when it is a suitable distance from the camera
    if (entity->hasComponent<NotOnPatrolYet>())
    {
        if (tf.position.x - (cam.target.x + SIZE::SCREEN.x/2) <= 100)
        {
            patrol.velocity.x = -100;
            if (rb.onGround == true) 
            {
                patrol.velocity.y = -700;
                rb.onGround = false;
            }

            patrol.lastDirection = Direction::Left;
            entity->removeComponent<NotOnPatrolYet>();
        }
    }

    // Koopa will jump if it is on the ground
    if (rb.onGround == true)
    {
        patrol.velocity.y = -700;
        rb.onGround = false;
    }
    else patrol.velocity.y = 0;

    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
    else rb.velocity.y += -1000 * dt; // anti-gravity -> fall longer
}