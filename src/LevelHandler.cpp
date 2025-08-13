#include <fstream>

#include <Factories/ItemFactory.hpp>

#include <Gameplay/Enemy/Goomba/Goomba.hpp>
#include <Gameplay/Enemy/Koopa/Koopa.hpp>
#include <Gameplay/Enemy/Koopa/KoopaJumping.hpp>
#include <Gameplay/Enemy/Koopa/KoopaFlying.hpp>
#include <Gameplay/Enemy/Piranha/Piranha.hpp>
#include <Gameplay/Tele/Components.hpp>
#include <Gameplay/Enemy/Lakitu/Lakitu.hpp>
#include <Gameplay/Enemy/Bowser/Bowser.hpp>
#include <Gameplay/GameProperties/GameSession.hpp>

#include <LevelHandler.hpp>

#include <Prefabs/Block.hpp>
#include <Prefabs/Pipe.hpp>
#include <Prefabs/Mario.hpp>
#include <Prefabs/Background.hpp>
#include <Prefabs/Coin.hpp>
#include <Prefabs/Fireworks.hpp>
#include <Prefabs/Podoboo.hpp>
#include <Prefabs/FireBar.hpp>
#include <Prefabs/Bridge.hpp>
#include <Prefabs/Elevator.hpp>
#include <Prefabs/Bell.hpp>

LevelHandler::LevelHandler(World &world, int currentLevel) : world(world), currentLevel(currentLevel) {}

void LevelHandler::start()
{
    switch (currentLevel)
    {
    case 1:
        // Load character setup from a JSON file
        load("assets/Levels/map11b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map11.json", world);

        spriteIndex = 1;
        world.createEntity<SmallCoin>(325.0f, 65.0f, 15, 24, ItemFactory(spriteIndex));

        break;
    case 2:
        // Load character setup from a JSON file
        load("assets/Levels/map61b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map61.json", world);

        spriteIndex = 1;
        world.createEntity<SmallCoin>(325.0f, 65.0f, 15, 24, ItemFactory(spriteIndex));

        break;
    case 3:
        // Load character setup from a JSON file
        load("assets/Levels/map54b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/map54.json", world);

        spriteIndex = 3;
        world.createEntity<SmallCoin>(325.0f, 65.0f, 15, 24, ItemFactory(spriteIndex));

        break;
    default:
        // Load character setup from a JSON file
        load("assets/Levels/menu1b.json", world);
        // Load the level setup from a JSON file
        load("assets/Levels/menu1.json", world);
        spriteIndex = 1;
    }
    world.createEntity<GameSession>(currentLevel, spriteIndex);
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
    char lastChar = tilename.back();
    int tileIndex = lastChar - '0';

    BlockFactory blockFactory(tileIndex);

    if (tilename.find("1UpBlock") != std::string::npos) // 1Up blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 8, blockFactory);
    }
    else if (tilename.find("NormalBlock") != std::string::npos) // Normal blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 5, blockFactory);
    }
    else if (tilename.find("CoinBlock") != std::string::npos) // Coin blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 6, blockFactory);
    }
    else if (tilename.find("FlagBlock") != std::string::npos) // Flag blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 10, blockFactory);
    }
    else if (tilename.find("StarBlock") != std::string::npos) // Star blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 9, blockFactory);
    }
    else if (tilename.find("CoinQuestionBlock") != std::string::npos) // Coin question blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 1, blockFactory);
    }
    else if (tilename.find("MushroomQuestionBlock") != std::string::npos) // Mushroom question blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 2, blockFactory);
    }
    else if (tilename.find("FlowerQuestionBlock") != std::string::npos) // Flower question blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 3, blockFactory);
    }
    else if (tilename.find("StairsBlock") != std::string::npos) // Stairs blocks
    {
        world.createEntity<Block>(x, y, width, height, scale, 7, blockFactory);
    }
    else if (tilename.find("MushroomBlock") != std::string::npos)
    {
        world.createEntity<Block>(x, y, width, height, scale, 11, blockFactory);
    }
    else if (tilename.find("Level1QuestionBlock") != std::string::npos)
    {
        world.createEntity<Block>(x, y, width, height, scale, 12, blockFactory);
    }
    else if (tilename.find("Level2QuestionBlock") != std::string::npos)
    {
        world.createEntity<Block>(x, y, width, height, scale, 13, blockFactory);
    }
    else if (tilename.find("Level3QuestionBlock") != std::string::npos)
    {
        world.createEntity<Block>(x, y, width, height, scale, 14, blockFactory);
    }
    else if (tilename.find("Level4QuestionBlock") != std::string::npos)
    {
        world.createEntity<Block>(x, y, width, height, scale, 15, blockFactory);
    }
}

void LevelHandler::pipeLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    char lastChar = tilename.back();
    int pipeIndex = lastChar - '0';

    PipeFactory pipeFactory(pipeIndex);

    if (tilename.find("HorizontalEnterablePipe") != std::string::npos)
    {
        auto pipe = world.createEntity<Pipe>(x, y, width * 4, height * 2, scale, 2, true, pipeFactory);
        pipe->addComponent<TelePort>();
        auto &teleport = pipe->getComponent<TelePort>();
        teleport.setCollideDir(Direction::Left);
        teleport.setDestination(teleMap["CheckPoint2"]);
        teleport.setInTimeTele(sf::Vector2f(200.f, 0.f));

        pipe->addComponent<hasPipeDestination>(Direction::Top);
    }
    else if (tilename.find("VerticalEnterablePipe") != std::string::npos) // Vertical go-in pipes
    {
        auto pipe = world.createEntity<Pipe>(x, y, width * 2, height, scale, 0, true, pipeFactory);
        pipe->addComponent<TelePort>();
        auto &teleport = pipe->getComponent<TelePort>();
        teleport.setCollideDir(Direction::Top);
        teleport.setDestination(teleMap["CheckPoint1"]);
        teleport.setInTimeTele(sf::Vector2f(0.f, 100.f));
    }
    else if (tilename.find("UnenterablePipe") != std::string::npos) // Nap cong
    {
        world.createEntity<Pipe>(x, y, width * 2, height, scale, 0, false, pipeFactory);
    }
    else if (tilename.find("Pipe") != std::string::npos) // Normal pipes
    {
        world.createEntity<Pipe>(x, y, width * 2, height, scale, 1, false, pipeFactory);
    }
}

void LevelHandler::groundLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "GroundBlock") // Ground block
    {
        world.createEntity<Block>(x, y, width, height, scale, -1, 0);
    }
    else if (tilename == "StairsBlock")
    {
        world.createEntity<Block>(x, y, width, height, scale, 0, 0);
    }
}

void LevelHandler::itemLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "BigCoin2" || tilename == "BigCoin1" || tilename == "BigCoin3") // Coin
    {
        char lastChar = tilename.back();
        int coinIndex = lastChar - '0';
        world.createEntity<Coin2>(x, y, width, height, scale, coinIndex);
    }
    else if (tilename == "FireBullet_4")
    {
        Fireworks::positions.push_back(sf::Vector2f(x, y));
    }
    else if (tilename == "Podoboo1")
    {
        world.createEntity<Podoboo>(x + width / 2, y, width, height, scale, true);
    }
    else if (tilename == "Podoboo2")
    {
        world.createEntity<Podoboo>(x + width / 2, y, width, height, scale, false);
    }
    else if (tilename == "FireBar1")
    {
        world.createEntity<FireBar>(x + 4, y + 4, scale, 1, ItemFactory(spriteIndex));
    }
    else if (tilename == "FireBar2")
    {
        world.createEntity<FireBar>(x + 4, y + 4, scale, 2, ItemFactory(spriteIndex));
    }
    else if (tilename == "Bridge1")
    {
        world.createEntity<Bridge>(x, y, scale, 1, ItemFactory(spriteIndex));
    }
    else if (tilename == "Bridge2")
    {
        world.createEntity<Bridge>(x, y, scale, 2, ItemFactory(spriteIndex));
    }
    else if (tilename == "SmallUpElevator")
    {
        world.createEntity<Elevator>(x, y, scale, 1, 1, ItemFactory(spriteIndex));
    }
    else if (tilename == "SmallDownElevator")
    {
        world.createEntity<Elevator>(x, y, scale, 1, 2, ItemFactory(spriteIndex));
    }
    else if (tilename == "MediumRightElevator")
    {
        world.createEntity<Elevator>(x, y, scale, 2, 4, ItemFactory(spriteIndex));
    }
    else if (tilename == "Bell")
    {
        world.createEntity<Bell>(x, y, width, height, scale, ItemFactory(spriteIndex));
    }
}

void LevelHandler::backgroundLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "FlagPole") // Background
    {
        world.createEntity<Background>(x, y, width, height, scale, 9);
        float flagPosX = x - width / 2;
        float flagPosY = y + 17;
        world.createEntity<Background>(flagPosX, flagPosY, 16, 16, scale, 10);
    }
    else if (tilename == "Castle")
    {
        world.createEntity<Background>(x, y, width, height, scale, 0);
    }
    else if (tilename == "Princess")
    {
        world.createEntity<Background>(x, y, width, height, scale, 12);
    }
}

void LevelHandler::playerLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "StartingPoint") // Player
    {
        world.createEntity<Mario>(x, y, width, height, scale);
    }
    else if (tilename == "CheckPoint1")
    {
        // world.createEntity<Mario>(x, y, width, height, 3);
        teleMap[tilename] = sf::Vector2f(x * scale, y * scale);
    }

    else if (tilename == "CheckPoint2")
    {
        teleMap[tilename] = sf::Vector2f(x * scale, y * scale);
    }
    else if (tilename == "CheckPoint3")
    {
        teleMap[tilename] = sf::Vector2f(x * scale, y * scale);
    }
}

void LevelHandler::enemyLoad(World &world, std::string tilename, float x, float y, float width, float height)
{
    if (tilename == "Goomba") // Goomba
    {
        // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
        auto goomba = world.createEntity<Goomba>(x, y, scale);
    }
    else if (tilename == "Koopa") // Koopa
    {
        auto koopa = world.createEntity<Koopa>(x, y, scale);
    }
    else if (tilename == "Piranha")
    {
        auto piranha = world.createEntity<Piranha>(x + width / 2, y + 16/3.0f, scale);
    }
    else if (tilename == "JumpingKoopa")
    {
        auto koopaJumping = world.createEntity<KoopaJumping>(x, y, scale);
    }
    else if (tilename == "FlyingKoopa")
    {
        auto koopaFlying = world.createEntity<KoopaFlying>(x, y, scale);
    }
    else if (tilename == "Lakitu")
    {
        auto lakitu = world.createEntity<Lakitu>(x, y, scale);
    }
    else if (tilename == "Bowser")
    {
        auto bowser = world.createEntity<Bowser>(x, y, scale);
    }
}