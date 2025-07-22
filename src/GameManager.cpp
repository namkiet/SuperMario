#include <GameManager.hpp>

#include <Engine/Animation/AnimationSystem.hpp>
#include <Engine/Camera/CameraSystem.hpp>
#include <Engine/Core/DespawnSystem.hpp>
#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <Engine/Physics/HitBlockSystem.hpp>
#include <Engine/Physics/GravitySystem.hpp>
#include <Engine/Physics/MovementSystem.hpp>
#include <Engine/Rendering/RenderSystem.hpp>

#include <Gameplay/Patrol/PatrolSystem.hpp>
#include <Gameplay/LifeSpan/LifeSpanSystem.hpp>

#include <Gameplay/Player/InputSystem.hpp>
#include <Gameplay/Player/HandlePlayerInputSystem.hpp>
#include <Gameplay/Player/PlayerRespawnSystem.hpp>
#include <Gameplay/Player/PlayerStateSystem.hpp>

#include <Gameplay/Reset/ResetSystem.hpp>
#include <Gameplay/Stomp/StompSystem.hpp>

#include <Gameplay/HitBlock/Hit1UpBlockSystem.hpp>
#include <Gameplay/HitBlock/HitStarBlockSystem.hpp>
#include <Gameplay/HitBlock/HitNormalBlockSystem.hpp>
#include <Gameplay/HitBlock/HitQuestionBlockSystem.hpp>
#include <Gameplay/HitBlock/HitCoinBlockSystem.hpp>

#include <Gameplay/Block/BounceBlockSystem.hpp>

#include <Gameplay/Popup/PopupSystem.hpp>

#include <Gameplay/DamageOnContact/DamageOnContactSystem.hpp>

#include <Gameplay/Item/ItemEmergingSystem.hpp>
#include <Gameplay/Item/CoinJumpingSystem.hpp>
#include <Gameplay/Item/DebrisSystem.hpp>
#include <Gameplay/Item/StarJumpingSystem.hpp>
#include <Gameplay/Item/FireBulletSystem.hpp>

#include <Gameplay/Collect/CollectSystem.hpp>

#include <Gameplay/Fire/FireSystem.hpp>

#include <cassert>
#include <iostream>

GameManager::GameManager():levelHandler(world)
{
    // Add some Entities
    // for (int i = 0; i < 50; i++)
    // {
    //     world.createEntity<Tile>(i * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y, "assets/floor_block.png");
    // }
    // auto player = world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50);

    // for (int i = 0; i < 3; i++)
    // {
    //     auto goomba = world.createEntity<Enemy>(2000 + 100 * i, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200);
    // }

    // world.createEntity<Tile>(50, SIZE::SCREEN.y - 2 * SIZE::GRID.y, "assets/platform_block.png");

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

    // auto block = world.createEntity();
    // block->addComponent<BlockTag>();
    // block->addComponent<QuestionBlockTag>();
    // block->addComponent<Transform>(sf::Vector2f(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4), SIZE::GRID);
    // block->addComponent<BoxCollider2D>(SIZE::GRID);
    // block->addComponent<Animation>(TextureManager::load("assets/coin_block.png"), 16, 16, 3, 0.3f);

    // world.createEntity<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 3 * SIZE::GRID.y);

    levelHandler.start();

    world.createEntity()->addComponent<Camera>();

    // Register Systems
    // world.addSystem<GravitySystem>();
    // world.addSystem<MovementSystem>();

    // world.addSystem<CollisionDetectionSystem>();
    // world.addSystem<HitBlockSystem>();

    // world.addSystem<PlayerInputSystem>();
    // world.addSystem<PlayerStateSystem>();

    // world.addSystem<CameraSystem>();
    // world.addSystem<AnimationSystem>();
    // world.addSystem<RenderSystem>();

    // world.addSystem<LifeSystem>();

    // world.addSystem<PopupSystem>();
    // world.addSystem<PatrolSystem>();
    // world.addSystem<StompSystem>();
    // world.addSystem<HitQuestionBlockSystem>();
    // world.addSystem<DamageOnContactSystem>();

    // world.addSystem<DespawnSystem>();
    // world.addSystem<PlayerRespawnSystem>();

    // phase 1
    world.addSystem<ResetSystem>();
    world.addSystem<InputSystem>();
    // phase 2
    world.addSystem<HandlePlayerInputSystem>();
    world.addSystem<GravitySystem>();

    // phase
    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<HitBlockSystem>();
    world.addSystem<PopupSystem>();
    world.addSystem<PatrolSystem>();
    world.addSystem<StompSystem>();
    world.addSystem<HitQuestionBlockSystem>();
    world.addSystem<BounceBlockSystem>();
    world.addSystem<DamageOnContactSystem>();
    world.addSystem<LifeSystem>();
    world.addSystem<CollectSystem>();
    world.addSystem<ItemEmergingSystem>();
    world.addSystem<CoinJumpingSystem>();
    world.addSystem<HitNormalBlockSystem>();
    world.addSystem<DebrisSystem>();
    world.addSystem<Hit1UpBlockSystem>();
    world.addSystem<HitStarBlockSystem>();
    world.addSystem<StarJumpingSystem>();
    world.addSystem<HitCoinBlockSystem>();
    world.addSystem<FireSystem>();
    world.addSystem<FireBulletSystem>();

    // phase 4
    world.addSystem<MovementSystem>();
    world.addSystem<PlayerStateSystem>();
    world.addSystem<DespawnSystem>();
    world.addSystem<PlayerRespawnSystem>();

    // phase 5
    world.addSystem<CameraSystem>();
    world.addSystem<AnimationSystem>();
    world.addSystem<RenderSystem>();
}

void GameManager::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::N)
        {
            // auto goomba = world.createEntity<Enemy>(350, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 300.f);
        }
    }
}

void GameManager::update(float dt)
{
    world.update(dt);
}

void GameManager::draw(sf::RenderWindow &window) const
{
    world.getSystem<RenderSystem>()->draw(world, window);
}