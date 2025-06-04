#pragma once

#include <SFML/Graphics.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>
#include <System.hpp>

class World
{
public:
                            World();
    void                    handleEvent(const sf::Event& event);
    void                    update(float dt);
    void                    draw(sf::RenderWindow& window) const;

private:
    std::unique_ptr<Mario>  player;
    std::unique_ptr<Enemy>  goomba;
    MovementSystem          movementSystem;
    RenderSystem            renderSystem;
};
