#pragma once
#include <SFML/Graphics.hpp>
#include <Mario.hpp>
#include <Enemy.hpp>
#include <System.hpp>

class Game
{
public:
                            Game();
    void                    run();

private:
    void                    handleEvent();
    void                    update(float dt);
    void                    draw();

private:
    sf::ContextSettings     contextSettings;
    sf::RenderWindow        window;
    std::unique_ptr<Mario>  player;
    std::unique_ptr<Enemy>  goomba;
    MovementSystem          movementSystem;
    RenderSystem            renderSystem;
};