#include <GameManager.hpp>
#include <Components/Declaration.hpp>
#include <Systems/Declaration.hpp>
#include <Coin.hpp>
#include <Enemy.hpp>
#include <Mario.hpp>
#include <Tile.hpp>
#include <Pipe.hpp>
#include <iostream>

GameManager::GameManager()
{
    for (int i = 0; i < 20; i++)
    {
        world.createEntity(std::make_unique<Tile>(i * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y, "assets/floor_block.png"));
    }
    auto player = world.createEntity(std::make_unique<Mario>(200, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 100)); 
    auto goomba = world.createEntity(std::make_unique<Enemy>(300, SIZE::SCREEN.y - 2 * SIZE::GRID.y - 200));

    // world.createEntity(std::make_unique<Tile>(5 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png"));    
    world.createEntity(std::make_unique<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png"));    
    world.createEntity(std::make_unique<Tile>(6 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png"));   
    world.createEntity(std::make_unique<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png"));   
    world.createEntity(std::make_unique<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png"));   
    world.createEntity(std::make_unique<Tile>(7 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png"));     
    world.createEntity(std::make_unique<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 2, "assets/platform_block.png"));     
    world.createEntity(std::make_unique<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3, "assets/platform_block.png"));     
    world.createEntity(std::make_unique<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 4, "assets/platform_block.png"));     
    world.createEntity(std::make_unique<Tile>(8 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 5, "assets/platform_block.png"));  

    pipe = world.createEntity(std::make_unique<Pipe>(15 * SIZE::GRID.x, SIZE::SCREEN.y - SIZE::GRID.y * 3));  
    
    auto camera = world.createEntity();
    camera->addComponent<Camera>();

    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();
    
    world.addSystem<PlayerEnemyCollisionSystem>();
    world.addSystem<CollisionSystem>();

    world.addSystem<PlayerInputSystem>();
    world.addSystem<ControlSystem>();
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
            auto goomba = world.createEntity(std::make_unique<Enemy>(300, SIZE::SCREEN.y - 2 * SIZE::GRID.y ));
        }
    }
}

void GameManager::update(float dt)
{
    auto player = world.findFirst<PlayerTag>();
    // std::cout << player->getComponent<RigidBody>().onGround;
    // auto& posP = player->getComponent<Transform>().position;
    // std::cout << posP.x << " " << posP.y << "\n";

    // std::cout << pipe->getComponent<Transform>().position.x << " " << pipe->getComponent<Transform>().position.y << "\n";
    // std::cout << pipe->getComponent<BoxCollider2D>().size.x << " " << pipe->getComponent<BoxCollider2D>().size.y << "\n";

    world.update(dt);
}

void GameManager::draw(sf::RenderWindow& window) const
{
    world.getSystem<RenderSystem>()->draw(world, window);
}