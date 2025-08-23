#include <Framework/World.hpp>
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Koopa/KoopaNormalBehaviour.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaNormalBehaviour::collideWithPlayer(Entity* entity)
{
    if (!entity->hasComponent<KoopaNormalTag>()) return;

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
            entity->addComponent<ChangeToKoopaShellTag>();
        }
        break;
    }
}


void KoopaNormalBehaviour::collideWithOther(Entity* entity)
{
    if (!entity->hasComponent<KoopaNormalTag>()) return;

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


void KoopaNormalBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<KoopaNormalTag>()) return;
    if (!entity->hasComponent<KoopaPatrol>()) return;

    auto& cam = world.findFirst<Camera>()->getComponent<Camera>();
    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& box = entity->getComponent<BoxCollider2D>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();
    auto& pox = tf.position;

    // Koopa starts patrolling when it is a suitable distance from the camera
    if (entity->hasComponent<NotOnPatrolYet>())
    {
        if (tf.position.x - (cam.target.x + SIZE::SCREEN.x/2) <= 100)
        {
            patrol.velocity = sf::Vector2f(-60, 0);
            patrol.lastDirection = Direction::Left;
            entity->removeComponent<NotOnPatrolYet>();
        }
    }

    bool stillOnGround = false;
    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (direction != Direction::Top) continue;

        auto bounds1 = Physics::GetCollisionBounds(entity);
        auto bounds2 = Physics::GetCollisionBounds(collider);
        auto centerX1 = bounds1.left + 0.5f * bounds1.width;
        auto centerX2 = bounds2.left + 0.5f * bounds2.width;
        auto dx = abs(centerX1 - centerX2);
        auto overlapX = 0.5f * (bounds1.width + bounds2.width) - dx;
        
        if (overlapX >= 0.25f * bounds1.width)
        {
            stillOnGround = true;
            break;
        }
    }

    if (stillOnGround == false && rb.onGround == true)
    {
        patrol.velocity.x *= -1;
        patrol.lastDirection = (patrol.velocity.x > 0 ? Direction::Right : Direction::Left);
    }

    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}