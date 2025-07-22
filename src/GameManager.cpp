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
#include <Gameplay/Player/PlayerInputSystem.hpp>
#include <Gameplay/Player/PlayerRespawnSystem.hpp>
#include <Gameplay/Player/PlayerStateSystem.hpp>
#include <Gameplay/Stomp/StompSystem.hpp>
#include <Gameplay/HitQuestionBlock/HitQuestionBlockSystem.hpp>
#include <Gameplay/Popup/PopupSystem.hpp>
#include <Gameplay/DamageOnContact/DamageOnContactSystem.hpp>
#include <Gameplay/BreakBrick/BreakBrickSystem.hpp>
#include <Gameplay/Fireball/BlockCollisionSystem.hpp>
#include <Gameplay/Fireball/ExplosionSystem.hpp>
#include <Gameplay/Fireball/DamageSystem.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Mario.hpp>
#include <Prefabs/Enemy.hpp>
#include <Prefabs/Piranha.hpp>
#include <Prefabs/Tile.hpp>
#include <Prefabs/Pipe.hpp>
#include <Prefabs/Fireball.hpp>
#include <iostream>

#include <Core/AnimationManager.hpp>
#include <Core/TextureManager.hpp>

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
        auto goomba = world.createEntity<Enemy>(2000 + 100 * i, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200);
    }

    auto brick = world.createEntity<Tile>(50, SIZE::SCREEN.y - 5 * SIZE::GRID.y, "assets/platform_block.png");  
    brick->addComponent<BrickTag>();

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

    world.createEntity<Piranha>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 2 * SIZE::GRID.y);
    
    auto block = world.createEntity();
    block->addComponent<BlockTag>();
    block->addComponent<QuestionBlockTag>();
    block->addComponent<Transform>(sf::Vector2f(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4), SIZE::GRID);
    block->addComponent<BoxCollider2D>(SIZE::GRID);
    block->addComponent<Animation>(TextureManager::load("assets/coin_block.png"), 16, 16, 3, 0.3f);

    world.createEntity<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - 3 * SIZE::GRID.y);

    world.createEntity()->addComponent<Camera>();

    // Register Systems
    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();

    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<HitBlockSystem>();


    world.addSystem<PlayerInputSystem>();
    world.addSystem<PlayerStateSystem>();

    world.addSystem<CameraSystem>();
    world.addSystem<AnimationSystem>();
    world.addSystem<RenderSystem>();
    
    world.addSystem<LifeSystem>();

    world.addSystem<PopupSystem>();
    world.addSystem<PatrolSystem>();
    world.addSystem<StompSystem>();
    world.addSystem<HitQuestionBlockSystem>();
    world.addSystem<DamageOnContactSystem>();

    world.addSystem<BreakBrickSystem>();

    world.addSystem<Fireball::BlockCollisionSystem>();
    world.addSystem<Fireball::ExplosionSystem>();
    world.addSystem<Fireball::DamageSystem>();

    world.addSystem<DespawnSystem>();
    world.addSystem<PlayerRespawnSystem>();
}

void GameManager::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::N)
        {
            auto goomba = world.createEntity<Enemy>(810, SIZE::SCREEN.y - 2 * SIZE::GRID.y);
        }

        if (event.key.code == sf::Keyboard::L)
        {
            world.findFirst<PlayerTag>()->addComponent<GrowUpTag>();
        }
        else if (event.key.code == sf::Keyboard::P)
        {
            world.createEntity<Prefab::Fireball>(760, SIZE::SCREEN.y - 2 * SIZE::GRID.y);
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