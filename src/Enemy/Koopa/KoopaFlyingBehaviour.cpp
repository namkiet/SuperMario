#include <World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Koopa/Components.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlyingBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaFlyingBehaviour::collideWithPlayer(Entity* entity)
{
    if (!entity->hasComponent<KoopaFlyingTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (direction == Direction::Bottom)
        {
            entity->addComponent<ChangeToKoopaNormalTag>();
            entity->getComponent<RigidBody>().velocity.y += 500;
            entity->getComponent<RigidBody>().applyGravity = true;
        }
        break;
    }
}


void KoopaFlyingBehaviour::collideWithOther(Entity* entity)
{
    if (!entity->hasComponent<KoopaFlyingTag>()) return;

    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<KoopaPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToKoopaFlippedTag>();
            entity->getComponent<RigidBody>().applyGravity = true;
        }
    }
}


void KoopaFlyingBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<KoopaFlyingTag>()) return;
    if (!entity->hasComponent<KoopaPatrol>()) return;
    if (!entity->hasComponent<KoopaFlyingPatrol>()) return;

    auto& cam = world.findFirst<Camera>()->getComponent<Camera>();
    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& flying = entity->getComponent<KoopaFlyingPatrol>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();

    // Koopa starts patrolling when it is a suitable distance from the camera
    if (entity->hasComponent<NotOnPatrolYet>())
    {
        if (tf.position.x - (cam.target.x + SIZE::SCREEN.x/2) <= 100)
        {
            flying.velocity.y = -50;

            patrol.lastDirection = Direction::Left;
            entity->removeComponent<NotOnPatrolYet>();
        }
    }

    if (!entity->hasComponent<NotOnPatrolYet>())
        flying.timer += dt;
    
    if (flying.timer > flying.phaseDuration)
    {
        flying.timer -= flying.phaseDuration;
        flying.velocity.y *= -1;
    }

    // Apply patrol velocity
    rb.velocity = flying.velocity;
    rb.applyGravity = false;
}