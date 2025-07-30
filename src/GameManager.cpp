#include <GameManager.hpp>

#include <Engine/Animation/AnimationSystem.hpp>
#include <Engine/Camera/CameraSystem.hpp>
#include <Engine/Core/DespawnSystem.hpp>
#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <Engine/Physics/HitBlockSystem.hpp>
#include <Engine/Physics/GravitySystem.hpp>
#include <Engine/Physics/MovementSystem.hpp>
#include <Engine/Rendering/RenderSystem.hpp>
#include <Engine/Rendering/DrawBoxColliderSystem.hpp>
#include <Engine/Rendering/DrawGameComponentSystem.hpp>

#include <Gameplay/Patrol/PatrolSystem.hpp>
#include <Gameplay/LifeSpan/LifeSpanSystem.hpp>

#include <Gameplay/Player/InputSystem.hpp>
#include <Gameplay/Player/HandlePlayerInputSystem.hpp>
#include <Gameplay/Player/PlayerRespawnSystem.hpp>
#include <Gameplay/Player/PlayerStateSystem.hpp>

#include <Gameplay/Reset/ResetSystem.hpp>
#include <Gameplay/Stomp/StompSystem.hpp>
#include <Gameplay/HitBlock/HitSpecialBlockSystem.hpp>
#include <Gameplay/Block/BounceBlockSystem.hpp>
#include <Gameplay/Popup/PopupSystem.hpp>
#include <Gameplay/DamageOnContact/DamageOnContactSystem.hpp>
#include <Gameplay/Invincible/InvincibleSystem.hpp>

#include <Gameplay/Item/ItemEmergingSystem.hpp>
#include <Gameplay/Item/CoinJumpingSystem.hpp>
#include <Gameplay/Item/DebrisSystem.hpp>
#include <Gameplay/Item/StarJumpingSystem.hpp>
#include <Gameplay/Item/FireBulletSystem.hpp>

#include <Gameplay/Collect/CollectSystem.hpp>
#include <Gameplay/Collect/CollectMushroomSystem.hpp>
#include <Gameplay/Collect/CollectFlowerSystem.hpp>
#include <Gameplay/Collect/CollectStarSystem.hpp>

#include <Gameplay/Fire/FireSystem.hpp>
#include <Gameplay/Tele/TeleSystem.hpp>

#include <Gameplay/Enemy/EnemyStateSystem.hpp>
#include <Gameplay/Enemy/EnemyBehaviourSystem.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumping.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlying.hpp>

#include <Gameplay/Score/PlayTimeSystem.hpp>
#include <Gameplay/Score/TextPoppingSystem.hpp>

#include <Gameplay/Background/FlagPoleSystem.hpp>
#include <Gameplay/Background/CastleSystem.hpp>

#include <cassert>
#include <iostream>

GameManager::GameManager() : levelHandler(world)
{
    levelHandler.start();

    world.createEntity()->addComponent<Camera>();

    world.addSystem<PlayTimeSystem>();
    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();

    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<HitBlockSystem>();

    world.addSystem<InputSystem>();
    world.addSystem<HandlePlayerInputSystem>();
    world.addSystem<PlayerStateSystem>();

    world.addSystem<CameraSystem>();
    world.addSystem<AnimationSystem>();
    world.addSystem<RenderSystem>();
    world.addSystem<DrawBoxColliderSystem>();
    world.addSystem<DrawGameComponentSystem>();

    world.addSystem<LifeSystem>();

    world.addSystem<PopupSystem>();
    world.addSystem<PatrolSystem>();
    world.addSystem<StompSystem>();
    world.addSystem<HitSpecialBlockSystem>();

    world.addSystem<TeleSystem>();
    world.addSystem<CollectSystem>();
    world.addSystem<CollectMushroomSystem>();
    world.addSystem<CollectFlowerSystem>();
    world.addSystem<CollectStarSystem>();

    world.addSystem<ItemEmergingSystem>();
    world.addSystem<CoinJumpingSystem>();
    world.addSystem<DebrisSystem>();
    world.addSystem<StarJumpingSystem>();
    world.addSystem<FireSystem>();
    world.addSystem<FireBulletSystem>();
    world.addSystem<BounceBlockSystem>();
    world.addSystem<FlagPoleCollisionSystem>();
    world.addSystem<CastleCollisionSystem>();
    world.addSystem<TextPoppingSystem>();
    world.addSystem<DamageOnContactSystem>();
    world.addSystem<InvincibleSystem>();
    world.addSystem<EnemyStateSystem>();
    world.addSystem<EnemyBehaviourSystem>();

    world.addSystem<DespawnSystem>();
    world.addSystem<PlayerRespawnSystem>();

    // phase 1
    // world.addSystem<ResetSystem>();
    // world.addSystem<InputSystem>();
    // phase 2
    // world.addSystem<HandlePlayerInputSystem>();
    // world.addSystem<GravitySystem>();

    // phase
    // world.addSystem<CollisionDetectionSystem>();
    // world.addSystem<HitBlockSystem>();
    // world.addSystem<PopupSystem>();
    // world.addSystem<PatrolSystem>();
    // world.addSystem<StompSystem>();
    // world.addSystem<BounceBlockSystem>();
    // world.addSystem<DamageOnContactSystem>();
    // world.addSystem<LifeSystem>();
    // world.addSystem<CollectSystem>();
    // world.addSystem<ItemEmergingSystem>();
    // world.addSystem<CoinJumpingSystem>();
    // world.addSystem<DebrisSystem>();
    // world.addSystem<StarJumpingSystem>();
    // world.addSystem<HitSpecialBlockSystem>();
    // world.addSystem<FireSystem>();
    // world.addSystem<FireBulletSystem>();

    // <<<<<<< HEAD
    //     world.addSystem<BreakBrickSystem>();

    //     world.addSystem<Fireball::BlockCollisionSystem>();
    //     world.addSystem<Fireball::ExplosionSystem>();
    //     world.addSystem<Fireball::DamageSystem>();

    // phase 4
    // world.addSystem<MovementSystem>();
    // world.addSystem<PlayerStateSystem>();
    // world.addSystem<DespawnSystem>();
    // world.addSystem<PlayerRespawnSystem>();

    // phase 5
    // world.addSystem<CameraSystem>();
    // world.addSystem<AnimationSystem>();
    // world.addSystem<RenderSystem>();
}

void GameManager::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::N)
        {
            // do nothing

            world.findFirst<PlayerTag>()->addComponent<InvincibleTag>(3.0f);
        }

        if (event.key.code == sf::Keyboard::X)
        {
            std::cout << "HELLO\n";
            auto koopa = world.createEntity<KoopaJumping>(30 * 16, 24 * 16, 3);
        }

        if (event.key.code == sf::Keyboard::T)
        {
            auto goomba = world.createEntity<Goomba>(20 * 16, 24 * 16, 3);
        }

        if (event.key.code == sf::Keyboard::P)
        {
            oneFrame = !oneFrame;
        }

        if (event.key.code == sf::Keyboard::O)
        {
            shouldPlay = true;
        }
    }
}

void GameManager::update(float dt)
{


    if (oneFrame && !shouldPlay) return;

    // std::cout << 1.0f / dt << "\n";
    

    world.update(dt);
    
    if (oneFrame)
    {
        shouldPlay = false;  
    }
}

void GameManager::draw(sf::RenderWindow &window) const
{
    // Set the custom view
    world.getSystem<RenderSystem>()->draw(world, window);

    // Drawn with custom view
    world.getSystem<DrawBoxColliderSystem>()->draw(world, window);

    // Set the default view
    world.getSystem<DrawGameComponentSystem>()->draw(world, window);
}
