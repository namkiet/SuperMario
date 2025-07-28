#include <GameManager.hpp>
#include <Engine/Animation/AnimationSystem.hpp>
#include <Engine/Camera/CameraSystem.hpp>
#include <Engine/Core/DespawnSystem.hpp>
#include <Engine/Physics/CollisionDetectionSystem.hpp>
#include <Engine/Physics/HitBlockSystem.hpp>
#include <Engine/Physics/GravitySystem.hpp>
#include <Engine/Physics/MovementSystem.hpp>
#include <Engine/Rendering/RenderSystem.hpp>
#include <Gameplay/LifeSpan/LifeSpanSystem.hpp>
#include <Gameplay/Player/PlayerInputSystem.hpp>
#include <Gameplay/Player/PlayerRespawnSystem.hpp>
#include <Gameplay/Player/PlayerStateSystem.hpp>
#include <Gameplay/Stomp/StompSystem.hpp>
#include <Gameplay/HitQuestionBlock/HitQuestionBlockSystem.hpp>
#include <Gameplay/DamageOnContact/DamageOnContactSystem.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Mario.hpp>
#include <Prefabs/Tile.hpp>
#include <Prefabs/Pipe.hpp>
#include <Prefabs/Enemy/Goomba/Goomba.hpp>
#include <Prefabs/Enemy/Koopa/Koopa.hpp> 
#include <Prefabs/Enemy/Koopa/KoopaJumping.hpp>
#include <Prefabs/Enemy/Koopa/KoopaFlying.hpp>
#include <Prefabs/Enemy/Piranha/Piranha.hpp>
#include <Prefabs/Enemy/EnemyBehaviourSystem.hpp>
#include <Prefabs/Enemy/EnemyStateSystem.hpp>
#include <iostream>

GameManager::GameManager()
{
    // Add some Entities
    for (int i = 0; i < 50; i++)
    {
        world.createEntity<Tile>(i * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y, "assets/floor_block.png");
    }
    auto player = world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50); 

    for (int i = 0; i < 3; i++)
    {
        auto goomba = world.createEntity<Goomba>(2000 + 100 * i, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200);
        auto koopa = world.createEntity<KoopaFlying>(1500 + 100 * i, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200);
    }

    world.createEntity<Tile>(50, SIZE::SCREEN.y - 2 * SIZE::GRID.y, "assets/platform_block.png");  

    world.createEntity<Tile>(5 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");    
    world.createEntity<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");    
    world.createEntity<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");   
    world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");   
    world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");   
    world.createEntity<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png");   
    world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png");     
    world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png");     
    world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png");     
    world.createEntity<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 5, "assets/platform_block.png");

    world.createEntity<Piranha>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 3 * SIZE::GRID.y);
    
    auto block = world.createEntity();
    block->addComponent<BlockTag>();
    block->addComponent<QuestionBlockTag>();
    block->addComponent<Transform>(sf::Vector2f(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4), SIZE::GRID);
    block->addComponent<BoxCollider2D>(SIZE::GRID);
    block->addComponent<Animation>(TextureManager::load("assets/coin_block.png"), 16, 16, 3, 0.3f);

    world.createEntity<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 3 * SIZE::GRID.y);

    world.createEntity()->addComponent<Camera>();

    // // Register Systems
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
    // // world.addSystem<PatrolSystem>();
    // world.addSystem<StompSystem>();
    // world.addSystem<HitQuestionBlockSystem>();
    // world.addSystem<DamageOnContactSystem>();

    // world.addSystem<DespawnSystem>();
    // world.addSystem<PlayerRespawnSystem>();

    // phase 1
    // world.addSystem<ResetSystem>();
    // world.addSystem<InputSystem>();
    // phase 2
    // world.addSystem<HandlePlayerInputSystem>();
    world.addSystem<GravitySystem>();

    // phase 3
    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<HitBlockSystem>();

    world.addSystem<PlayerInputSystem>();

    world.addSystem<StompSystem>();
    world.addSystem<HitQuestionBlockSystem>();
    world.addSystem<DamageOnContactSystem>();
    world.addSystem<LifeSystem>();
    world.addSystem<EnemyStateSystem>();
    world.addSystem<EnemyBehaviourSystem>();

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

void GameManager::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::N)
        {
            auto goomba = world.createEntity<Goomba>(300, SIZE::SCREEN.y - 2 * SIZE::GRID.y );
        }
    }
}

void GameManager::update(float dt)
{
    world.update(dt);
}

void GameManager::draw(sf::RenderWindow& window) const
{
    world.getSystem<RenderSystem>()->draw(world, window);
}