#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <World.hpp>

class LevelHandler
{
private:
    sf::Image levelImage;
    sf::Image enemyImage;
    sf::Image playerImage;
    sf::Image backgroundImage;

    World &world;
    // sf::RenderWindow &window;

    void loadImage();
    void setLevel();
    void setPlayer();
    void setEnemy();
    void setBackground();

public:
    LevelHandler() = default;
    LevelHandler(World &world);
    void start();
};