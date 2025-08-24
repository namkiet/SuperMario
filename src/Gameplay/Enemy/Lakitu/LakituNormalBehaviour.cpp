#include <Framework/World.hpp>
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Lakitu/Components.hpp>
#include <Gameplay/Enemy/Lakitu/LakituNormalBehaviour.hpp>
#include <Entity/Enemy/Spiny.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Core/Variables.hpp>
#include <iostream>

void LakituNormalBehaviour::collideWithPlayer(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (!collider->hasComponent<PlayerTag>()) continue;

        if (direction == Direction::Bottom)
        {
            entity->addComponent<ChangeToLakituFlippedTag>();
        }
        break;
    }
}


void LakituNormalBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->addComponent<ChangeToLakituFlippedTag>();
        }
    }
}


void LakituNormalBehaviour::patrol(Entity* entity, float dt, World& world)
{
    if (!entity->hasComponent<LakituPatrol>()) return;

    auto& patrol = entity->getComponent<LakituPatrol>();
    auto& rb = entity->getComponent<RigidBody>();
    auto& tf = entity->getComponent<Transform>();
    auto& towardPlayer = entity->getComponent<TowardPlayer>();

    // auto playerTf = world.findFirst<PlayerTag, Transform>()->getComponent<Transform>();
    // auto targetCenter = playerTf.position + (playerTf.size / 2.0f);
    auto lakituCenter = tf.position + (tf.size / 2.0f);
    Entity* player = world.findFirst<PlayerTag>();
    auto targetCenter = patrol.freeTarget;
    if (player) 
    {
        auto playerTf = player->getComponent<Transform>();
        targetCenter = playerTf.position + (playerTf.size / 2.0f);
    }
    if (targetCenter.x > patrol.limitX)
    targetCenter = patrol.freeTarget;

    if (abs(lakituCenter.x - targetCenter.x) > patrol.distance + 200)
    {
        if (lakituCenter.x < targetCenter.x)
        {
            patrol.lastDirection = Direction::Right;
        }
        else patrol.lastDirection = Direction::Left;

        patrol.velocity.x = patrol.fastSpeed * (patrol.lastDirection == Direction::Right ? 1 : -1);
        patrol.accelerate = 0;
        patrol.phase = PatrolPhase::Chase;
    }

    // This is used for the fast speed
    if (abs(lakituCenter.x - targetCenter.x) < patrol.distance && patrol.phase == PatrolPhase::Chase)
    {
        double d;
        if (patrol.lastDirection == Direction::Left)
        {
            d = lakituCenter.x - (targetCenter.x - patrol.distance);
        }
        else d = targetCenter.x + patrol.distance - lakituCenter.x;

        patrol.accelerate = (patrol.velocity.x * patrol.velocity.x) / (2 * d);
        
        if (patrol.lastDirection == Direction::Right)
            patrol.accelerate *= -1;
        
        patrol.phase = PatrolPhase::Oscillate;
    }

    // This is used for the slow speed
    if (abs(lakituCenter.x - targetCenter.x) < 25 && patrol.phase == PatrolPhase::Oscillate)
    {
        patrol.accelerate = (patrol.velocity.x * patrol.velocity.x) / (2 * patrol.distance);
        
        if (patrol.lastDirection == Direction::Right)
            patrol.accelerate *= -1;
        
        patrol.phase = PatrolPhase::Oscillate;
    }

    if (patrol.phase == PatrolPhase::Oscillate && abs(lakituCenter.x - (targetCenter.x - patrol.distance)) < 1)
    {
        patrol.accelerate = 70.0f;
        patrol.lastDirection = Direction::Right;

    }

    if (patrol.phase == PatrolPhase::Oscillate && abs(lakituCenter.x - (targetCenter.x + patrol.distance)) < 1)
    {
        patrol.accelerate = -70.0f;
        patrol.lastDirection = Direction::Left;
    }

    patrol.velocity.x += patrol.accelerate * dt;

        towardPlayer.direction = (tf.position.x < targetCenter.x ? Direction::Right : Direction::Left);


    // Apply patrol velocity
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}


void LakituNormalBehaviour::attack(Entity* entity, float dt, World& world)
{
    auto& attack = entity->getComponent<LakituAttack>();
    auto tf = entity->getComponent<Transform>();
    auto rb = entity->getComponent<RigidBody>();

    auto playerPos = world.findFirst<PlayerTag, Transform>()->getComponent<Transform>().position;

    if (abs(playerPos.x - tf.position.x) > attack.distance) 
        return;

    attack.timer += dt;

    if (attack.delay - attack.timer <= 0.5f)
    {
        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Lakitu/lakitu_attack.png"));
        entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("lakitu_attack"), 16, 24, 1, 0.0f);
    }
    
    if (attack.timer >= attack.delay)
    {
        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Lakitu/lakitu_normal.png"));
        entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("lakitu_normal"), 16, 24, 1, 0.0f);

        attack.timer -= attack.delay;
            
        auto spiny = world.createEntity<Spiny>(0.0f, 0.0f, 3.0f);
        auto& spinyTf = spiny->getComponent<Transform>();
        auto& spinyRb = spiny->getComponent<RigidBody>();
        auto& spinyPatrol = spiny->getComponent<SpinyPatrol>();
            
        spinyTf.position = sf::Vector2f(tf.position.x, tf.position.y - spinyTf.size.y);
        spinyPatrol.velocity.x = playerPos.x - tf.position.x;
        spinyRb.velocity.y = -700;
    }
}