#include <GameManager.hpp>
#include <Components/Declaration.hpp>
#include <Systems/Declaration.hpp>
#include <Coin.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>
#include <Tile.hpp>
#include <Pipe.hpp>
#include <iostream>

GameManager::GameManager()
{
    for (int i = 0; i < 50; i++)
    {
        // if (i == 3)
        world.createEntity<Tile>(i * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y, "assets/floor_block.png");
    }
    auto player = world.createEntity<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 50); 
    auto goomba = world.createEntity<Enemy>(300, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200);

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
    
    auto block = world.createEntity();
    block->addComponent<BlockTag>(BlockType::QUESTION_BLOCK);
    block->addComponent<Transform>(sf::Vector2f(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4), SIZE::GRID);
    block->addComponent<BoxCollider2D>(SIZE::GRID);
    block->addComponent<Animation>(TextureManager::load("assets/coin_block.png"), 16, 16, 3, 0.3f);

    world.createEntity<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3);

    world.createEntity()->addComponent<Camera>();

    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();

    world.addSystem<CollisionDetectionSystem>();
    world.addSystem<CollisionResolutionSystem>();
    world.addSystem<PlayerCollisionSystem>();

    world.addSystem<PlayerInputSystem>();
    world.addSystem<EnemyAISystem>();

    world.addSystem<PlayerStateSystem>();

    world.addSystem<CameraSystem>();
    world.addSystem<AnimationSystem>();
    
    world.addSystem<LifeSystem>();
    world.addSystem<RenderSystem>();
}

void GameManager::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::N)
        {
            auto goomba = world.createEntity<Enemy>(300, SIZE::SCREEN.y - 2 * SIZE::GRID.y );
        }
    }
}

void GameManager::update(float dt)
{
    auto player = world.findFirst<EnemyTag>();
    if (player)
    {
        std::cout << player->getComponent<RigidBody>().velocity.x << "\n";
    }
    // // std::cout << player->getComponent<BoxCollider2D>().collisions.size() << "\n";
    // std::cout << player->getComponent<RigidBody>().velocity.y << " " << player->getComponent<RigidBody>().velocity.y << "\n";

    world.update(dt);
}

void GameManager::draw(sf::RenderWindow& window) const
{
    world.getSystem<RenderSystem>()->draw(world, window);
}