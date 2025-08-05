#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <World.hpp>
#include <Engine/Core/Transform.hpp>
#include <string>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <iostream>
class LevelHandler
{
private:
    World &world;
    int currentLevel = 0;
    // 1 for world 1-1
    // 2 for world 5-4
    // 3 for world 6-1 + 6-2
    int spriteIndex = 0;

    std::unordered_map<std::string, sf::Vector2f> teleMap;

    void tileLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void pipeLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void groundLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void itemLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void backgroundLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void playerLoad(World &world, std::string tilename, float x, float y, float width, float height);
    void enemyLoad(World &world, std::string tilename, float x, float y, float width, float height);

    void load(const std::string &filename, World &world);

public:
    LevelHandler(World &world, int currentLevel = 0);
    void start();
};