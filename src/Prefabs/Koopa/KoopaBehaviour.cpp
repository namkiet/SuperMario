#include <ECS/Entity.hpp>
#include <Prefabs/Enemy/Koopa/KoopaBehaviour.hpp>
#include <Prefabs/Enemy/Components.hpp>
#include <Prefabs/Enemy/Koopa/Components.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Core/Physics.hpp>
#include <Core/Variables.hpp>
#include <Gameplay/Player/Components.hpp>
#include <iostream>

void KoopaBehaviour::collideWithPlayer(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (entity->hasComponent<KoopaNormalTag>())
        {
            if (direction == Direction::Bottom)
            {
                entity->addComponent<ChangeToKoopaShellTag>();
            }
        }

        if (entity->hasComponent<KoopaShellTag>())
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

        if (entity->hasComponent<KoopaSlideTag>())
        {
            if (direction == Direction::Bottom)
            {
                entity->addComponent<ChangeToKoopaShellTag>();
            }
        }

        break;
    }
}


void KoopaBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<KoopaPatrol>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (collider->hasComponent<PlayerTag>()) continue;

        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToKoopaFlippedTag>();
        }

        if (entity->hasComponent<CanKillEnemyTag>() && collider->hasComponent<EnemyTag>()) continue;
        
        if (direction == Direction::Left && patrol.lastDirection == Direction::Right)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Left;
        }
        if (direction == Direction::Right && patrol.lastDirection == Direction::Left)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Right;
        }
    }
}


void KoopaBehaviour::activatePatrol(Entity* entity, Entity* camera)
{
    if (!entity->hasComponent<NotOnPatrolYet>()) return;

    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& tf = entity->getComponent<Transform>();
    auto& cam = camera->getComponent<Camera>();

    if (tf.position.x - (cam.target.x + SIZE::SCREEN.x/2) <= 100)
    {
        patrol.velocity = sf::Vector2f(-30, 0);
        patrol.lastDirection = Direction::Left;
        entity->removeComponent<NotOnPatrolYet>();
    }
}


void KoopaBehaviour::patrol(Entity* entity, float dt)
{
    if (!entity->hasComponent<KoopaPatrol>()) return;

    auto& patrol = entity->getComponent<KoopaPatrol>();
    auto& box = entity->getComponent<BoxCollider2D>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();
    auto& pox = tf.position;

    // Koopa will turn back when it will fall if they are still moving in current direction
    if (entity->hasComponent<KoopaNormalTag>())
    {
        pox.x += (patrol.velocity.x + rb.velocity.x) * dt;
        pox.y += (patrol.velocity.y + rb.velocity.y) * dt;
        
        bool stillOnGround = false;
        for (auto& [collider, direction] : box.collisions)
            if (Physics::GetCollisionDirection(entity, collider) == Direction::Top)
            {
                stillOnGround = true;
                break;
            }
        
        pox.x -= (patrol.velocity.x + rb.velocity.x) * dt;
        pox.y -= (patrol.velocity.y + rb.velocity.y) * dt;
        
        if (stillOnGround == false && rb.onGround == true)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = (patrol.velocity.x > 0 ? Direction::Right : Direction::Left);
        }
    }

    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}