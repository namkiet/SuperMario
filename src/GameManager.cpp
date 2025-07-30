#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Goomba/Goomba.hpp>
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
#include <Gameplay/CaptureFlag/CaptureFlagSystem.hpp>
#include <Gameplay/CaptureFlag/SlideOnFlagPoleSystem.hpp>

#include <Gameplay/Enemy/EnemyStateSystem.hpp>
#include <Gameplay/Enemy/EnemyBehaviourSystem.hpp>

#include <cassert>
#include <iostream>


#include <Gameplay/Enemy/Koopa/KoopaJumping.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlying.hpp>

// <<<<<<< HEAD
// #include <Gameplay/BreakBrick/BreakBrickSystem.hpp>
// #include <Gameplay/Fireball/BlockCollisionSystem.hpp>
// #include <Gameplay/Fireball/ExplosionSystem.hpp>
// #include <Gameplay/Fireball/DamageSystem.hpp>
// #include <Prefabs/Coin.hpp>
// #include <Prefabs/Mario.hpp>
// #include <Prefabs/Enemy.hpp>
// #include <Prefabs/Piranha.hpp>
// #include <Prefabs/Tile.hpp>
// #include <Prefabs/Pipe.hpp>
// #include <Prefabs/Fireball.hpp>
// #include <iostream>

// #include <Core/AnimationManager.hpp>
// #include <Core/TextureManager.hpp>

// GameManager::GameManager()
// =======

GameManager::GameManager() : levelHandler(world)
{

    // Add some Entities
    // for (int i = 0; i < 50; i++)
    // {
    //     world.createEntity<Tile>(i * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y, "assets/floor_block.png");
    // }
    // auto player = world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50);

    

    // auto brick = world.createEntity<Tile>(50, SIZE::SCREEN.y - 5 * SIZE::GRID.y, "assets/platform_block.png");
    // brick->addComponent<BrickTag>();

    // world.createEntity<Tile>(5 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");
    // world.createEntity<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");
    // world.createEntity<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");
    // world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");
    // world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");
    // world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png");
    // world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");
    // world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");
    // world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png");
    // world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 5, "assets/platform_block.png");

    // world.createEntity<Piranha>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 2 * SIZE::GRID.y);

    // auto flag = world.createEntity();
    // flag->addComponent<Transform>(sf::Vector2f(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4), SIZE::GRID);
    // flag->addComponent<BoxCollider2D>();
    // flag->addComponent<QuestionBlockTag>();
    // flag->addComponent<BoxCollider2D>(SIZE::GRID);
    // flag->addComponent<Animation>(TextureManager::load("assets/coin_block.png"), 16, 16, 3, 0.3f);

    // world.createEntity<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 3 * SIZE::GRID.y);

    levelHandler.start();

    world.createEntity()->addComponent<Camera>();

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

    world.addSystem<CaptureFlagSystem>();
    world.addSystem<SlideOnFlagPoleSystem>();

    world.addSystem<ItemEmergingSystem>();
    world.addSystem<CoinJumpingSystem>();
    world.addSystem<DebrisSystem>();
    world.addSystem<StarJumpingSystem>(); 
    world.addSystem<FireSystem>();
    world.addSystem<FireBulletSystem>();
    world.addSystem<BounceBlockSystem>();
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

            // world.findFirst<PlayerTag>()->addComponent<WaitComponent>(3.0f);
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
    world.getSystem<RenderSystem>()->draw(world, window);
    world.getSystem<DrawBoxColliderSystem>()->draw(world, window);
}
