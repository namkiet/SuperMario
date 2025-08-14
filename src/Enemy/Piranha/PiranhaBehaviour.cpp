#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Piranha/Components.hpp>
#include <Gameplay/Enemy/Piranha/PiranhaBehaviour.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Audio/Components.hpp>
#include <Engine/Audio/SoundManager.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/GameProperties/Components.hpp>

void PiranhaBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}

void PiranhaBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<SoundComponent>(&SoundManager::load("assets/Sounds/kickkill.wav"));
            entity->addComponent<DespawnTag>();
            // Add score tag to notify the score system
            entity->addComponent<ShouldUpdateScore>(200);
            break;
        }
    }
}


void PiranhaBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<PiranhaPatrol>()) return;

    auto& patrol = entity->getComponent<PiranhaPatrol>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();

    if (tf.position.y <= patrol.minHeight)
    {
        tf.position.y = patrol.minHeight;
        patrol.timer += dt;
    }
    else if (tf.position.y >= patrol.maxHeight)
    {
        tf.position.y = patrol.maxHeight;
        patrol.timer += dt;
    }

    if (patrol.timer >= patrol.delay)
    {
        patrol.timer = 0;
        patrol.velocity.y *= -1;
    }

    if (patrol.timer == 0)
    {
        rb.velocity = patrol.velocity;
    }
    else
    {
        rb.velocity = sf::Vector2f(0, 0);
    }
}