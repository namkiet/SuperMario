#include <iostream>
#include <LevelHandler.hpp>
#include <Prefabs/Block.hpp>
#include <Prefabs/Pipe.hpp>
#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumping.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlying.hpp>
#include <Gameplay/Enemy/Piranha/Piranha.hpp>
#include <Prefabs/Mario.hpp>
#include <Prefabs/Background.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Fireworks.hpp>
#include <iostream>
#include <Gameplay/Tele/Components.hpp>
using namespace std;

LevelHandler::LevelHandler(World &world, int currentLevel) : world(world), currentLevel(currentLevel) {}

void LevelHandler::start()
{
    world.createEntity<SmallCoin>(325, 65, 15, 24);
    cout << "Current level: " << currentLevel << endl;
    switch (currentLevel)
    {
    case 1:
        // Load character setup from a JSON file
        load("assets/Levels/map11b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map11.json", world);
        break;
    case 2:
        // Load character setup from a JSON file
        load("assets/Levels/map54b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map54.json", world);
        break;
    case 3:
        // Load character setup from a JSON file
        load("assets/Levels/map61b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map61.json", world);
        break;
    }
}

void LevelHandler::load(const std::string &filename, World &world)
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
    if (tilename == "1UpBlock") // 1Up blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 8);
    }
    else if (tilename == "NormalBlock") // Normal blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 5);
    }
    else if (tilename == "CoinBlock") // Coin blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 6);
    }
    else if (tilename == "FlagBlock") // Flag blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 10);
    }
    else if (tilename == "StarBlock") // Star blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 9);
    }
    else if (tilename == "CoinQuestionBlock") // Coin question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 1);
    }
    else if (tilename == "MushroomQuestionBlock") // Mushroom question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 2);
    }
    else if (tilename == "FlowerQuestionBlock") // Flower question blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 3);
    }
    else if (tilename == "StairsBlock") // Stairs blocks
    {
        world.createEntity<Block>(x, y, width, height, 3, 7);
    }
}

void LevelHandler::pipeLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "UnenterablePipe") // Nap cong
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 0, false);
    }
    else if (tilename == "Pipe") // Normal pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, 3, 1, false);
    }
    else if (tilename == "HorizontalEnterablePipe")
    {
        auto pipe = world.createEntity<Pipe>(x, y, width * 3, height * 2, 3, 2, true);
        pipe->addComponent<TelePort>();
        auto &teleport = pipe->getComponent<TelePort>();
        teleport.setCollideDir(Direction::Left);
        teleport.setDestination(teleMap["CheckPoint2"]);
        teleport.setInTimeTele(sf::Vector2f(200.f, 0.f));

        pipe->addComponent<hasPipeDestination>(Direction::Top);
    }
    else if (tilename == "VerticalEnterablePipe") // Vertical go-in pipes
    {
        auto pipe = world.createEntity<Pipe>(x, y, width * 2, height, 3, 0, true);
        pipe->addComponent<TelePort>();
        auto &teleport = pipe->getComponent<TelePort>();
        teleport.setCollideDir(Direction::Top);
        teleport.setDestination(teleMap["CheckPoint1"]);
        teleport.setInTimeTele(sf::Vector2f(0.f, 100.f));
    }
}

void LevelHandler::groundLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "GroundBlock") // Ground block
    {
        world.createEntity<Block>(x, y, width, height, 3, -1);
    }
}

void LevelHandler::itemLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Coin2_5") // Coin
    {
        world.createEntity<Coin2>(x, y, width, height, 3);
    }
    else if (tilename == "FireBullet_4")
    {
        Fireworks::positions.push_back(sf::Vector2f(x, y));
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
    else if (tilename == "Castle")
    {
        world.createEntityAtFront<Background>(x, y, width, height, 3, 0);
    }
}

void LevelHandler::playerLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "StartingPoint") // Player
    {
        world.createEntityAtFront<Mario>(x, y, width, height, 3);
    }
    else if (tilename == "CheckPoint1")
    {
        // world.createEntity<Mario>(x, y, width, height, 3);
        teleMap[tilename] = sf::Vector2f(x * 3, y * 3);
    }

    else if (tilename == "CheckPoint2")
    {
        teleMap[tilename] = sf::Vector2f(x * 3, y * 3);
    }
    else if (tilename == "CheckPoint3")
    {
        teleMap[tilename] = sf::Vector2f(x * 3, y * 3);
    }
}

void LevelHandler::enemyLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Goomba") // Goomba
    {
        // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
        auto goomba = world.createEntity<Goomba>(x, y, 3);
    }
    else if (tilename == "Koopa") // Koopa
    {
        auto koopa = world.createEntity<Koopa>(x, y, 3);
    }
    else if (tilename == "Piranha")
    {
        auto piranha = world.createEntity<Piranha>(x + width / 2, y, 3);
    }
    else if (tilename == "JumpingKoopa")
    {
        auto koopaJumping = world.createEntity<KoopaJumping>(x, y, 3);
    }
    else if (tilename == "FlyingKoopa")
    {
        auto koopaFlying = world.createEntity<KoopaFlying>(x, y, 3);
    }
}