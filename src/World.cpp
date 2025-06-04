#include <World.hpp>

World::World()
{
    player = std::make_unique<Mario>(100, 200);
    goomba = std::make_unique<Enemy>(500, 100);

    movementSystem.addEntity(player.get());
    renderSystem.addEntity(player.get());

    movementSystem.addEntity(goomba.get());
    renderSystem.addEntity(goomba.get());
}

void World::handleEvent(const sf::Event& event)
{

}

void World::update(float dt)
{
    movementSystem.update(dt);
}

void World::draw(sf::RenderWindow& window) const
{
    renderSystem.draw(window);
}