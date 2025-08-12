#include <Framework/World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBulletBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <iostream>

void BowserBulletBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserBulletBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void BowserBulletBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& patrol = entity->getComponent<BowserBulletPatrol>();
    auto& tf = entity->getComponent<Transform>();
    auto& rb = entity->getComponent<RigidBody>();

    if (abs(tf.position.y + patrol.velocity.y * dt - patrol.targetY) > abs(tf.position.y - patrol.targetY))
    {
        patrol.velocity.y = 0;
    }

    rb.velocity = patrol.velocity;
}
