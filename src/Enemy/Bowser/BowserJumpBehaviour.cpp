#include <World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserJumpBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <Core/Physics.hpp>

void BowserJumpBehaviour::collideWithPlayer(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<BowserPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<PlayerTag>())
        {
            if (direction == Direction::Bottom && !entity->hasComponent<ChangeToBowserHurtTag>())
            {
                entity->getComponent<Health>().hp--;
                if (entity->getComponent<Health>().hp > 0)
                {
                    entity->addComponent<ChangeToBowserHurtTag>();
                }
                else entity->addComponent<ChangeToBowserDeadTag>();
                break;
            }
        }
    }
}


void BowserJumpBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<BowserPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>() && !entity->hasComponent<ChangeToBowserHurtTag>())
        {
            entity->getComponent<Health>().hp--;
                if (entity->getComponent<Health>().hp > 0)
                {
                    entity->addComponent<ChangeToBowserHurtTag>();
                }
                else entity->addComponent<ChangeToBowserDeadTag>();
        }
    }
}


void BowserJumpBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& patrol = entity->getComponent<BowserPatrol>();
    auto& tf = entity->getComponent<Transform>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& playerTF = world.findFirst<PlayerTag>()->getComponent<Transform>();
    auto& towardPlayer = entity->getComponent<TowardPlayer>();
    auto playerCen = playerTF.position + playerTF.size / 2.0f;

    if (rb.onGround == true)
    {
        entity->addComponent<ChangeToBowserWalkTag>();
        return;
    }

    towardPlayer.direction = (tf.position.x < playerTF.position.x ? Direction::Right : Direction::Left);

    if (playerCen.x >= tf.position.x && playerCen.x <= tf.position.x + tf.size.x && playerCen.y > tf.position.y)
    {
        patrol.velocity.y = 1200;
    }

    // Apply patrol
    rb.velocity.x = patrol.velocity.x;
    if (rb.velocity.y != 0)
    {
        if (playerCen.x >= tf.position.x && playerCen.x <= tf.position.x + tf.size.x && playerCen.y > tf.position.y)
        {
            rb.velocity.y += 7000 * dt; // accelerate to stomp player
        }
        else
        {
            rb.velocity.y += -1000 * dt; // anti-gravity
        }
    }
}
