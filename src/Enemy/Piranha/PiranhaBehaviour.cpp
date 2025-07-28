#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Piranha/Components.hpp>
#include <Gameplay/Enemy/Piranha/PiranhaBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Gameplay/Player/Components.hpp>

void PiranhaBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}

void PiranhaBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<DespawnTag>();
            break;
        }
    }
}


void PiranhaBehaviour::patrol(Entity* entity, float dt, Entity* camera)
{
    if (!entity->hasComponent<PiranhaPatrol>()) return;

    auto& patrol = entity->getComponent<PiranhaPatrol>();
    auto& rb = entity->getComponent<RigidBody>();

    patrol.timer += dt;
    if (patrol.timer > patrol.phaseDuration + patrol.delay)
    {
        patrol.timer -= patrol.phaseDuration + patrol.delay;
        patrol.velocity.y *= -1;
    }

    if (patrol.timer <= patrol.phaseDuration)
    {
        rb.velocity = patrol.velocity;
    }
    else 
    {
        rb.velocity = sf::Vector2f(0, 0);
    }
}