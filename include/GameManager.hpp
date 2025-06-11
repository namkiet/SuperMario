#pragma once

#include <SFML/Graphics.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>
#include <Ground.hpp>
#include <World.hpp>

class GameManager
{
public:
                            GameManager();
    void                    handleEvent(const sf::Event& event);
    void                    update(float dt);
    void                    draw(sf::RenderWindow& window) const;

private:
    std::unique_ptr<Mario>  player;
    std::unique_ptr<Enemy>  goomba;
    std::unique_ptr<Ground> ground;

    // MovementSystem          movementSystem;
    // RenderSystem            renderSystem;
    // PlayerInputSystem       playerInputSystem;
    // PlayerControlSystem     playerControlSystem;
    // GravitySystem           gravitySystem;
    // ColliderSystem          colliderSystem;
    World                   world;
};
