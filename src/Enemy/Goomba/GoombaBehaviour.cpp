#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Goomba/Components.hpp>
#include <Gameplay/Enemy/Goomba/GoombaBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>

void GoombaBehaviour::collideWithPlayer(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (direction == Direction::Bottom)
        {
            entity->addComponent<ChangeToGoombaStompedTag>();
        }
        break;
    }
}


void GoombaBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<GoombaPatrol>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToGoombaFlippedTag>();
        }
        else if (direction == Direction::Left && patrol.velocity.x > 0)
        {
            // exit(0);
            patrol.velocity.x *= -1;
        }
        else if (direction == Direction::Right && patrol.velocity.x < 0)
        {
            // exit(0);
            patrol.velocity.x *= -1;
        }
    }
}


void GoombaBehaviour::patrol(Entity* entity, float dt, Entity* camera)
{
    if (!entity->hasComponent<GoombaPatrol>()) return;

    auto& patrol = entity->getComponent<GoombaPatrol>();
    auto& rb = entity->getComponent<RigidBody>();

    // Goomba starts patrolling when it is a suitable distance from the camera
    if (entity->hasComponent<NotOnPatrolYet>())
    {
        auto& tf = entity->getComponent<Transform>();
        auto& cam = camera->getComponent<Camera>();
        
        if (tf.position.x - (cam.target.x + SIZE::SCREEN.x/2) <= 100)
        {
            patrol.velocity = sf::Vector2f(-60, 0);
            entity->removeComponent<NotOnPatrolYet>();
        }
    }    

    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}