#include <Framework/World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserSlideBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <Core/Physics.hpp>

void BowserSlideBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserSlideBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<BowserPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<PlayerTag>()) continue;
        if (collider->hasComponent<EnemyTag>()) continue;
        if (collider->hasComponent<CanKillEnemyTag>()) continue;
        
        if (direction == Direction::Left && patrol.lastDirection == Direction::Right)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Left;
        }
        else if (direction == Direction::Right && patrol.lastDirection == Direction::Left)
        {
            patrol.velocity.x *= -1;
            patrol.lastDirection = Direction::Right;
        }
    }
}


void BowserSlideBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& patrol = entity->getComponent<BowserPatrol>();
    auto& box = entity->getComponent<BoxCollider2D>();
    auto& tf = entity->getComponent<Transform>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& playerTF = world.findFirst<PlayerTag>()->getComponent<Transform>();

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

    if (rb.onGround == true && stillOnGround == false)
    {
        if (patrol.lastDirection == Direction::Left)
        {
            patrol.lastDirection = Direction::Right;
        }
        else patrol.lastDirection = Direction::Left;
    }
    

    patrol.velocity.x = abs(patrol.velocity.x) * (patrol.lastDirection == Direction::Right ? 1 : -1);

    entity->getComponent<TowardPlayer>().direction = (tf.position.x < playerTF.position.x ? Direction::Right : Direction::Left);


    // Apply patrol
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}
