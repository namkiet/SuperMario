#include <World.hpp>
#include <ECS/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserIdleBehaviour.hpp>
#include <Gameplay/Enemy/Bowser/BowserBullet/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>

void BowserIdleBehaviour::collideWithPlayer(Entity* entity)
{
    // no-op
}


void BowserIdleBehaviour::collideWithOther(Entity* entity)
{
    const auto& box = entity->getComponent<BoxCollider2D>();
    auto& patrol = entity->getComponent<BowserPatrol>();

    for (auto& [collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<CanKillEnemyTag>())
        {
            entity->getComponent<Health>().hp--;
            entity->addComponent<ChangeToBowserHurtTag>();
        }
    }
}


void BowserIdleBehaviour::patrol(Entity* entity, float dt, World& world)
{
    auto& bowserTF =entity->getComponent<Transform>();
    auto& attack = entity->getComponent<BowserAttack>();
    auto playerTF = world.findFirst<PlayerTag>()->getComponent<Transform>();

    if (abs(bowserTF.position.x - playerTF.position.x) <= attack.distance)
    {
        entity->addComponent<ChangeToBowserWalkTag>();
    }
}


void BowserIdleBehaviour::attack(Entity* entity, float dt, World& world)
{
    if (entity->hasComponent<ChangeToBowserWalkTag>() 
    ||  entity->hasComponent<ChangeToBowserDeadTag>())
    {
        return;
    }

    auto& bowserTF =entity->getComponent<Transform>();
    auto& attack = entity->getComponent<BowserAttack>();
    auto playerTF = world.findFirst<PlayerTag>()->getComponent<Transform>();

    if (abs(bowserTF.position.x - playerTF.position.x) > attack.distance)
    {
        return;
    }

    if (entity->getComponent<Health>().hp == 2)
    {
        attack.delay = 3;
    }
    else if (entity->getComponent<Health>().hp == 1)
    {
        attack.delay = 2;
    }

    attack.timer += dt;

    if (attack.isShooting == 0 && attack.castTime > 0 && attack.timer + dt >= attack.castTime)
    {
        attack.isShooting = 0;
        attack.castTime = 0;

        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_idle.png"));
        anim.frameWidth = 32;
        anim.frameHeight = 35;
        anim.frameCount = 1;
        anim.frameDuration = 0;
        anim.currentFrame = 0;
        anim.timer = 0;
    }
    else if (attack.delay > attack.timer && attack.delay - attack.timer <= 0.75f && attack.isShooting == 0)
    {
        attack.isShooting = 1;
        attack.castTime = (attack.delay - attack.timer) / 2;

        auto& anim = entity->getComponent<Animation>();
        anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_shoot.png"));
        anim.frameWidth = 32;
        anim.frameHeight = 36;
        anim.frameCount = 2;
        anim.frameDuration = (attack.delay - attack.timer);
        anim.currentFrame = 0;
        anim.timer = 0;

        anim.sprite.setTextureRect(sf::IntRect(
            anim.currentFrame * anim.frameWidth,
            anim.row * anim.frameHeight,
            anim.frameWidth,
            anim.frameHeight
        ));
    }
    else if (attack.timer >= attack.delay)
    {
        attack.timer -= attack.delay;
        attack.castTime += attack.timer;
        attack.isShooting = 0;

        auto bullet = world.createEntity<BowserBullet>(0, 0, 3);
        auto& bulletTF = bullet->getComponent<Transform>();
        auto& bulletPT = bullet->getComponent<BowserBulletPatrol>();
        auto direction = entity->getComponent<TowardPlayer>().direction;

        if (direction == Direction::Left)
        {
            bulletTF.position.x = bowserTF.position.x - bulletTF.size.x;
        }
        else 
        {
            bulletTF.position.x = bowserTF.position.x + bowserTF.size.x;
        }

        bulletTF.position.y = bowserTF.position.y;
        bulletPT.velocity.x = 250 * (direction == Direction::Right ? 1 : -1);
        bulletPT.velocity.y = 250 * (playerTF.position.y - bulletTF.position.y > 0 ? 1 : -1);
        bulletPT.targetY = playerTF.position.y;
    }
}