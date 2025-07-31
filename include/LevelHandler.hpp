#pragma once
#include <SFML/Graphics.hpp>
#include <Core/TextureManager.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <World.hpp>
#include <Engine/Core/Transform.hpp>
#include <string>
#include <string>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
class LevelHandler
{
private:
    World &world;
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
    LevelHandler(World &world);
    void start();
};