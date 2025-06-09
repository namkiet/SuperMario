#include <World.hpp>

World::World()
{
    player = std::make_unique<Mario>(100, 200);
    goomba = std::make_unique<Enemy>(500, 200);
    ground = std::make_unique<Ground>(100, 300);

    playerInputSystem.addEntity(player.get());
    playerControlSystem.addEntity(player.get());
    gravitySystem.addEntity(player.get());

    movementSystem.addEntity(player.get());
    movementSystem.addEntity(goomba.get());

    renderSystem.addEntity(player.get());
    renderSystem.addEntity(goomba.get());
    renderSystem.addEntity(ground.get());

    colliderSystem.addEntity(ground.get());
    colliderSystem.addEntity(player.get());
    // colliderSystem.addEntity(goomba.get());  
}

void World::handleEvent(const sf::Event& event)
{

}

void World::update(float dt)
{
    playerInputSystem.update(dt);
    playerControlSystem.update(dt);
    movementSystem.update(dt);
    gravitySystem.update(dt);
    colliderSystem.update(dt);
}

void World::draw(sf::RenderWindow& window) const
{
    renderSystem.draw(window);
}