#include <GameManager.hpp>
#include <Components/Declaration.hpp>
#include <Systems/Declaration.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>

GameManager::GameManager()
{
    auto player = world.createEntity(std::make_unique<Mario>(200, 100)); 
    // auto goomba = world.createEntity(std::make_unique<Enemy>(500, 100));

    auto camera = world.createEntity();
    camera->addComponent<Camera>();

    world.addSystem<AnimationSystem>();
    // world.addSystem<CameraSystem>();
    world.addSystem<ColliderSystem>();
    world.addSystem<GravitySystem>();
    world.addSystem<MovementSystem>();
    world.addSystem<PlayerControlSystem>();
    world.addSystem<PlayerInputSystem>();
    world.addSystem<RenderSystem>();
    world.addSystem<StateSystem>();
}

void GameManager::handleEvent(const sf::Event& event)
{

}

void GameManager::update(float dt)
{
    world.update(dt);
}

void GameManager::draw(sf::RenderWindow& window) const
{
    world.getSystem<RenderSystem>()->draw(world, window);
}