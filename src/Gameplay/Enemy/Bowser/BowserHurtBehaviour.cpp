#include <Framework/World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserHurtBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <Core/Physics.hpp>

void BowserHurtBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserHurtBehaviour::collideWithOther(Entity* entity)
{
    // no-op
}


void BowserHurtBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& stateDur = entity->getComponent<StateDuration>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& anim = entity->getComponent<Animation>();

    stateDur.timer += dt;

    if (stateDur.duration == 0)
    {
        if (rb.onGround == true)
            stateDur.duration = 2;
    }
    else
    {
        rb.velocity = sf::Vector2f(0, 0);
        if (stateDur.timer > stateDur.duration)
            entity->addComponent<ChangeToBowserSkidTag>();
    }
}
