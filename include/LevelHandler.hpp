#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
// #include <World.hpp>

// class LevelHandler
// {
// private:
//     sf::Image levelImage;
//     sf::Image enemyImage;
//     sf::Image playerImage;
//     sf::Image backgroundImage;

//     World &world;
//     // sf::RenderWindow &window;

// public:
//     LevelHandler() = delete;
//     LevelHandler(World &world);
//     void start();
// };

#include <fstream>
#include <nlohmann/json.hpp>
#include <World.hpp>
#include <Engine/Core/Transform.hpp>
#include <string>

class LevelHandler
{
private:
    World &world;
    sf::Image levelImage;
    sf::Image enemyImage;
    sf::Image playerImage;
    sf::Image backgroundImage;
    void tileLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void pipeLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void groundLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void itemLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void loadImage();
    // void setLevel();
    void setPlayer();
    void setEnemy();
    void setBackground();
    void loadMap(const std::string &filename, World &world);

public:
    LevelHandler(World &world);
    void start();
};