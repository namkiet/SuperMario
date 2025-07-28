#include <iostream>
#include <LevelHandler.hpp>
#include <Prefabs/Block.hpp>
#include <Prefabs/Pipe.hpp>
#include <Prefabs/Enemy.hpp>
#include <Prefabs/Mario.hpp>
#include <Prefabs/Background.hpp>
#include <Prefabs/Coin.hpp>
#include <iostream>
using namespace std;

LevelHandler::LevelHandler(World &world) : world(world) {}

void LevelHandler::start()
{
    world.createEntity<SmallCoin>(325, 65, 15, 24);
    loadMap("assets/Levels/map11.json", world);
}

void LevelHandler::loadMap(const std::string &filename, World &world)
{
    std::ifstream file(filename);
    nlohmann::json mapJson;
    file >> mapJson;

    int tileWidth = mapJson["tilewidth"];
    int tileHeight = mapJson["tileheight"];

    // --- Build tileId to name map ---
    std::unordered_map<int, std::string> idToName;
    for (const auto &tileset : mapJson["tilesets"])
    {
        int firstgid = tileset["firstgid"];
        std::string name = tileset["name"];
        idToName[firstgid] = name;
    }

    // --- Load tile layer ---
    for (const auto &layer : mapJson["layers"])
    {
        if (layer["type"] == "tilelayer")
        {
            int layerWidth = layer["width"];
            auto &data = layer["data"];
            for (size_t i = 0; i < data.size(); ++i)
            {
                int tileId = data[i];
                if (tileId == 0)
                    continue;

                int col = i % layerWidth;
                int row = i / layerWidth;
                float x = static_cast<float>(col * tileWidth);
                float y = static_cast<float>(row * tileHeight);

                std::string tileName;
                if (idToName.count(tileId))
                {
                    tileName = idToName[tileId];
                }
                else
                {
                    continue;
                }
                tileLoad(world, tileName, x, y, tileWidth, tileHeight);
                pipeLoad(world, tileName, x, y, tileWidth, tileHeight);
                itemLoad(world, tileName, x, y, tileWidth, tileHeight);
                playerLoad(world, tileName, x, y, tileWidth, tileHeight);
                enemyLoad(world, tileName, x, y, tileWidth, tileHeight);
            }
        }

        // --- Load object layer ---
        else if (layer["type"] == "objectgroup")
        {
            for (const auto &obj : layer["objects"])
            {
                float x = obj["x"];
                float y = obj["y"];
                float width = obj["width"];
                float height = obj["height"];
                std::string objName = obj["name"];

                groundLoad(world, objName, x, y, width, height);
                backgroundLoad(world, objName, x, y, width, height);
            }
        }
    }
}

void LevelHandler::tileLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Tile1_1") // 1Up blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 8);
    }
    else if (tilename == "Tile1_2") // Normal blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 5);
    }
    else if (tilename == "Tile1_8") // Flag blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 10);
    }
    else if (tilename == "Tile1_17") // Star blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 9);
    }
    else if (tilename == "Tile1_24") // Coin question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 1);
    }
    else if (tilename == "Tile1_25") // Mushroom question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 2);
    }
    else if (tilename == "Tile1_26") // Flower question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 3);
    }
    else if (tilename == "Tile1_28") // Stairs blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 7);
    }
}

void LevelHandler::pipeLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Pipe1_0") // Nap cong
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 0, false);
    }
    else if (tilename == "Pipe1_1") // Normal pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 1, false);
    }
    else if (tilename == "Pipe1_2")
    {
        world.createEntity<Pipe>(x, y, width * 3, height * 2, 3, 2, true);
    }
    else if (tilename == "Pipe2_0") // Vertical go-in pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 0, true);
    }
    else if (tilename == "Pipe2_1") // Vertical go-out pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 1, true);
    }
    else if (tilename == "Pipe5_0") // Horizontal go-out pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 0, false);
    }
    else if (tilename == "Pipe5_1") // Vertical go-out pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 1, false);
    }
}

void LevelHandler::groundLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Ground1") // Ground block
    {
        world.createEntity<Block>(x, y, width, height, 3, -1);
    }
    else if (tilename == "Ground2") // Ground block with different texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -2);
    }
    else if (tilename == "Ground3") // Ground block with another texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -3);
    }
    else if (tilename == "Ground4") // Ground block with yet another texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -4);
    }
    else if (tilename == "Ground5") // Ground block with a different texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -5);
    }
    else if (tilename == "Ground6") // Ground block with another texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -6);
    }
    else if (tilename == "Ground7") // Ground block with yet another texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -7);
    }
    else if (tilename == "Ground8") // Ground block with a different texture
    {
        world.createEntity<Block>(x, y, width, height, 3, -8);
    }
}

void LevelHandler::itemLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Coin2_5") // Coin
    {
        world.createEntity<Coin2>(x, y, width, height, 3);
    }
}

void LevelHandler::backgroundLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "FlagPole") // Background
    {
        world.createEntity<Background>(x, y, width, height, 3, 9);
        float flagPosX = x - width / 2;
        float flagPosY = y + 17;
        world.createEntity<Background>(flagPosX, flagPosY, 16, 16, 3, 10);
    }
}

void LevelHandler::playerLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "StartingPoint") // Player
    {
        world.createEntity<Mario>(x, y, width, height, 3);
    }
    else if (tilename == "CheckPoint")
    {
        // world.createEntity<Mario>(x, y, width, height, 3);
    }
}

void LevelHandler::enemyLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Goomba") // Goomba
    {
        world.createEntity<Enemy>(x, y, width, height, 3, 0);
    }
    else if (tilename == "Koopa") // Koopa
    {
        world.createEntity<Enemy>(x, y, width, height, 3, 1);
    }
}