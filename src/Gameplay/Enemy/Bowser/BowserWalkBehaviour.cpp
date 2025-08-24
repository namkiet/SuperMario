#include <Framework/World.hpp>
#include <Entity/Entity.hpp>
#include <Gameplay/Enemy/Components.hpp>
#include <Gameplay/Enemy/Bowser/Components.hpp>
#include <Gameplay/Enemy/Bowser/BowserWalkBehaviour.hpp>
#include <Entity/Enemy/BowserBullet.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <Engine/Core/RigidBody.hpp>
#include <Engine/Core/Transform.hpp>
#include <Gameplay/Player/Components.hpp>
#include <Gameplay/LifeSpan/Components.hpp>
#include <Core/Variables.hpp>
#include <Core/Physics.hpp>

void BowserWalkBehaviour::collideWithPlayer(Entity *entity)
{
    const auto &box = entity->getComponent<BoxCollider2D>();
    auto &patrol = entity->getComponent<BowserPatrol>();

    for (auto &[collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<PlayerTag>())
        {
            if ((direction == Direction::Bottom || collider->hasComponent<CanKillEnemyTag>()) && !entity->hasComponent<ChangeToBowserHurtTag>())
            {
                entity->getComponent<Health>().hp--;
                if (entity->getComponent<Health>().hp > 0)
                {
                    entity->addComponent<ChangeToBowserHurtTag>();
                }
                else
                    entity->addComponent<ChangeToBowserDeadTag>();

                break;
            }
        }
    }
}

void BowserWalkBehaviour::collideWithOther(Entity *entity)
{
    const auto &box = entity->getComponent<BoxCollider2D>();
    auto &patrol = entity->getComponent<BowserPatrol>();

    for (auto &[collider, direction, overlap] : box.collisions)
    {
        if (collider->hasComponent<PlayerTag>()) continue;

        if (collider->hasComponent<CanKillEnemyTag>() && !entity->hasComponent<ChangeToBowserHurtTag>())
        {
            entity->getComponent<Health>().hp--;
            if (entity->getComponent<Health>().hp > 0)
            {
                entity->addComponent<ChangeToBowserHurtTag>();
            }
            else
                entity->addComponent<ChangeToBowserDeadTag>();
        }
    }
}

void BowserWalkBehaviour::patrol(Entity *entity, float dt, World &world)
{
    auto &patrol = entity->getComponent<BowserPatrol>();
    auto &attack = entity->getComponent<BowserAttack>();
    auto &box = entity->getComponent<BoxCollider2D>();
    auto &tf = entity->getComponent<Transform>();
    auto &rb = entity->getComponent<RigidBody>();
    
    auto player = world.findFirst<PlayerTag, Transform>();
    if (!player) return;

    auto playerTF = player->getComponent<Transform>();


    if (attack.castTime > 0)
    {
        patrol.velocity = sf::Vector2f(0, 0);
    }
    else if (abs(tf.position.x - playerTF.position.x) > attack.distance)
    {
        entity->addComponent<ChangeToBowserIdleTag>();
    }
    else
    {
        auto bowserCen = tf.position + tf.size / 2.0f;
        auto playerCen = playerTF.position + playerTF.size / 2.0f;
        auto &towardPlayer = entity->getComponent<TowardPlayer>();

        if (patrol.lastDirection != towardPlayer.direction)
        {
            patrol.timerDura += dt;
        }
        else
            patrol.timerJump += dt;

        bool stillOnGround = false;
        for (auto &[collider, direction, overlap] : box.collisions)
        {
            if (direction != Direction::Top)
                continue;

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

        if ((rb.onGround == true && stillOnGround == false) || (patrol.timerDura > patrol.duration && patrol.lastDirection != towardPlayer.direction) || (abs(bowserCen.x - playerCen.x) < patrol.safeDist))
        {
            patrol.timerDura = 0;

            if (patrol.lastDirection == Direction::Left)
            {
                patrol.lastDirection = Direction::Right;
            }
            else
                patrol.lastDirection = Direction::Left;

            if (!entity->hasComponent<ChangeToBowserJumpTag>())
            {
                entity->addComponent<ChangeToBowserJumpTag>();
            }

            return;
        }

        if (patrol.timerJump >= patrol.jumpCooldown)
        {
            patrol.timerJump = 0;
            if (!entity->hasComponent<ChangeToBowserJumpTag>())
            {
                entity->addComponent<ChangeToBowserJumpTag>();
            }
            return;
        }

        patrol.velocity.x = 50 * (patrol.lastDirection == Direction::Right ? 1 : -1);

        towardPlayer.direction = (tf.position.x < playerTF.position.x ? Direction::Right : Direction::Left);
    }

    // Apply patrol
    rb.velocity.x = patrol.velocity.x;
    if (patrol.velocity.y != 0)
    {
        rb.velocity.y = patrol.velocity.y;
    }
}

void BowserWalkBehaviour::attack(Entity *entity, float dt, World &world)
{
    auto &bowserTF = entity->getComponent<Transform>();
    auto &attack = entity->getComponent<BowserAttack>();
    
    auto player = world.findFirst<PlayerTag, Transform>();
    if (!player) return;

    auto playerTF = player->getComponent<Transform>();
    

    if (abs(bowserTF.position.x - playerTF.position.x) > attack.distance || entity->hasComponent<ChangeToBowserHurtTag>() || entity->hasComponent<ChangeToBowserDeadTag>())
    {
        attack.timer = 0;
        attack.castTime = 0;
        attack.isShooting = 0;
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

        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_walk.png"));
        // anim.textures.clear();
        // anim.frameWidth = 32;
        // anim.frameHeight = 35;
        // anim.frameCount = 4;
        // anim.frameDuration = 0.25f;
        // anim.currentFrame = 0;
        // anim.timer = 0;

        // anim.sprite.setTextureRect(sf::IntRect(
        //     anim.currentFrame * anim.frameWidth,
        //     anim.row * anim.frameHeight,
        //     anim.frameWidth,
        //     anim.frameHeight
        // ));
        entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_walk"), 32, 35, 4, 0.25f);
    }
    else if (attack.delay > attack.timer && attack.delay - attack.timer <= 0.75f && attack.isShooting == 0)
    {
        attack.isShooting = 1;
        attack.castTime = (attack.delay - attack.timer) / 2;

        // auto& anim = entity->getComponent<Animation>();
        // anim.sprite = sf::Sprite(TextureManager::load("assets/Enemy/Bowser/bowser_shoot.png"));
        // anim.frameWidth = 32;
        // anim.frameHeight = 36;
        // anim.frameCount = 2;
        // anim.frameDuration = (attack.delay - attack.timer);
        // anim.currentFrame = 0;
        // anim.timer = 0;

        // anim.sprite.setTextureRect(sf::IntRect(
        //     anim.currentFrame * anim.frameWidth,
        //     anim.row * anim.frameHeight,
        //     anim.frameWidth,
        //     anim.frameHeight
        // ));
        entity->addComponent<Animation>(EnemyFactory::getEnemyTexture("bowser_shoot"), 32, 36, 2, attack.delay - attack.timer);
    }
    else if (attack.timer >= attack.delay)
    {
        attack.timer = 0;
        attack.isShooting = 0;

        auto bullet = world.createEntity<BowserBullet>(0.0f, 0.0f, 3.0f);
        auto &bulletTF = bullet->getComponent<Transform>();
        auto &bulletPT = bullet->getComponent<BowserBulletPatrol>();
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