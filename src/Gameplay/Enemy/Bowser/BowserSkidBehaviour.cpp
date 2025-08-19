#include <Framework/World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserSkidBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <Core/Physics.hpp>

void BowserSkidBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserSkidBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void BowserSkidBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& patrol = entity->getComponent<BowserPatrol>();
    auto& tf = entity->getComponent<Transform>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& playerTF = world.findFirst<PlayerTag, Transform>()->getComponent<Transform>();
    auto& towardPlayer = entity->getComponent<TowardPlayer>();

    towardPlayer.direction = (tf.position.x < playerTF.position.x ? Direction::Right : Direction::Left);

    patrol.velocity.x = abs(patrol.velocity.x) * (towardPlayer.direction == Direction::Left ? 1 : -1);

    patrol.accelerate.x = abs(patrol.accelerate.x) * (towardPlayer.direction == Direction::Left ? -1 : 1);

    patrol.velocity += patrol.accelerate * dt;

    if (abs(patrol.velocity.x) < 3)
    {
        entity->addComponent<ChangeToBowserSlideTag>();
        return;
    }

    // Apply patrol
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}
