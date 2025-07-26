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

LevelHandler::LevelHandler(World &world) : world(world)
{
    loadImage();
}

void LevelHandler::loadImage()
{
    levelImage.loadFromFile("assets/Levels/map11.png");
    backgroundImage.loadFromFile("assets/Levels/map11b.png");
    enemyImage.loadFromFile("assets/Levels/map11c.png");
    playerImage.loadFromFile("assets/Levels/map11d.png");

    if (levelImage.getSize().x == 0 || levelImage.getSize().y == 0)
    {
        cerr << "Failed to load level image!" << endl;
        return;
    }
    if (enemyImage.getSize().x == 0 || enemyImage.getSize().y == 0)
    {
        cerr << "Failed to load character image!" << endl;
        return;
    }
    if (backgroundImage.getSize().x == 0 || backgroundImage.getSize().y == 0)
    {
        cerr << "Failed to load background image!" << endl;
        return;
    }
    if (playerImage.getSize().x == 0 || playerImage.getSize().y == 0)
    {
        cerr << "Failed to load player image!" << endl;
        return;
    }
}

void LevelHandler::setLevel()
{
    int width = levelImage.getSize().x;
    int height = levelImage.getSize().y;
    for (int j = 0; j < width; ++j)
    {
        for (int i = 0; i < height; ++i)
        {
            sf::Color pixelColor = levelImage.getPixel(j, i);
            // // cout << "Here" << endl;
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255) // White
            {
                continue; // Skip white pixels
            }
            else if (red == 0 && green == 0 && blue == 0) // Ground blocks
            {
                // cout << "Before adding ground block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 3360, 96, 3, -1);
                // cout << "Ground block added" << endl;
            }
            else if (red == 16 && green == 239 && blue == 234)
            {
                world.createEntity<Block>(j * 16, i * 16, 720, 96, 3, -2);
            }
            else if (red == 112 && green == 74 && blue == 181)
            {
                // cout << "Before adding pipe block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 3024, 96, 3, -3);
                // cout << "Pipe block added" << endl;
            }
            else if (red == 19 && green == 166 && blue == 236)
            {
                // cout << "Before adding go-in pipe block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 2928, 96, 3, -4);
                // cout << "Go-in pipe block added" << endl;
            }
            else if (red == 128 && green == 64 && blue == 64)
            {
                world.createEntity<Block>(j * 16, i * 16, 816, 96, 3, -5);
            }
            else if (red == 64 && green == 0 && blue == 128)
            {
                world.createEntity<Block>(j * 16, i * 16, 48, 528, 3, -6);
            }
            else if (red == 0 && green == 255 && blue == 0)
            {
                world.createEntity<Block>(j * 16, i * 16, 288, 144, 3, -7);
            }
            else if (red == 0 && green == 128 && blue == 128)
            {
                world.createEntity<Block>(j * 16, i * 16, 288, 48, 3, -8);
            }
            else if (red == 128 && green == 255 && blue == 128) // Question blocks for coin
            {
                // cout << "Before adding question block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 1);
                // cout << "Coin question block added" << endl;
            }
            else if (red == 128 && green == 128 && blue == 0) // Question blocks for mushroom
            {
                // cout << "Before adding mushroom question block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 2);
                // cout << "Mushroom question block added" << endl;
            }
            else if (red == 239 && green == 116 && blue == 236) // Question blocks for flower
            {
                // cout << "Before adding flower question block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 3);
                // cout << "Flower question block added" << endl;
            }
            else if (red == 242 && green == 234 && blue == 94) // Question blocks for star
            {
                // cout << "Before adding star question block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 4);
                // cout << "Star question block added" << endl;
            }
            else if (red == 128 && green == 128 && blue == 255) // Normal blocks
            {
                // cout << "Before adding normal block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 5);
                // cout << "Normal block added" << endl;
            }
            else if (red == 0 && green == 128 && blue == 0) // Coin blocks
            {
                // cout << "Before adding coin block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 6);
                // cout << "Coin block added" << endl;
            }
            else if (red == 255 && green == 0 && blue == 128) // Stairs
            {
                // cout << "Before adding stairs block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 7);
                // cout << "Stairs block added" << endl;
            }
            else if (red == 255 && green == 128 && blue == 64) // Level-up block
            {
                // cout << "Before adding level-up block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 8);
                // cout << "Level-up block added" << endl;
            }
            else if (red == 40 && green == 170 && blue == 170) // Star block
            {
                // cout << "Before adding star block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 9);
                // std::cout << "Star block added" << std::endl;
                // cout << "Star block added" << endl;
            }
            else if (red == 163 && green == 73 && blue == 164)
            {
                // cout << "Before adding flag block" << endl;
                world.createEntity<Block>(j * 16, i * 16, 16, 16, 3, 10);

                // cout << "Flag block added" << endl;
            }
            else if (red == 255 && green == 0 && blue == 0) // Nap cong
            {
                // cout << "Before adding pipe block" << endl;
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 0, false);
                // cout << "Pipe block added" << endl;
            }
            else if (red == 0 && green == 128 && blue == 255) // Normal pipes
            {
                // cout << "Before adding normal pipe block" << endl;
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 1, false);
                // cout << "Normal pipe added" << endl;
            }
            else if (red == 255 && green == 128 && blue == 128) // Go-in pipes
            {
                // cout << "Before adding go-in pipe block" << endl;
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 1, true);
                // cout << "Go-in pipe added" << endl;
            }
            else if (red == 185 && green == 122 && blue == 87) // Go-out pipes
            {
                // cout << "Before adding go-out pipe block" << endl;
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 1, true);
                // cout << "Go-out pipe added" << endl;
            }
            else if (red == 128 && green == 0 && blue == 64)
            {
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 2, true);
            }
            else if (red == 0 && green == 64 && blue == 128)
            {
                world.createEntity<Pipe>(j * 16, i * 16, 32, 16, 3, 3, true);
            }
        }
    }
}

void LevelHandler::setPlayer()
{
    int width = playerImage.getSize().x;
    int height = playerImage.getSize().y;
    bool playerSet = false;
    for (int j = 0; j < width && !playerSet; ++j)
    {
        for (int i = 0; i < height && !playerSet; ++i)
        {

            sf::Color pixelColor = playerImage.getPixel(j, i);
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255) // White
            {
                continue; // Skip white pixels
            }
            else if (red == 0 && green == 0 && blue == 0) // Black for player
            {
                // std::// cout << "Player starting position found at: (" << j << ", " << i << ")" << std::endl;
                auto player = world.createEntity<Mario>(j * 16, i * 16, 16, 16, 3);
                playerSet = true;
            }
        }
    }
}

void LevelHandler::setEnemy()
{
    int width = enemyImage.getSize().x;
    int height = enemyImage.getSize().y;
    int count = 0;
    for (int j = 0; j < width; ++j)
    {
        for (int i = 0; i < height; ++i)
        {

            sf::Color pixelColor = enemyImage.getPixel(j, i);
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255)
            {
                continue;
            }
            else if (red == 0 && green == 0 && blue == 0)
            {
                if (count >= 1)
                {
                    // // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
                    auto goomba = world.createEntity<Enemy>(j * 16, i * 16, 16, 16, 3, 0);
                }
            }
            else if (red == 255 && green == 174 && blue == 201)
            {
                if (count >= 1)
                {
                    // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
                    auto koopa = world.createEntity<Enemy>(j * 16, i * 16, 16, 24, 3, 1);
                }
            }
            ++count;
        }
    }
}

void LevelHandler::setBackground()
{
    int width = backgroundImage.getSize().x;
    int height = backgroundImage.getSize().y;
    for (int j = 0; j < width; ++j)
    {
        for (int i = 0; i < height; ++i)
        {
            sf::Color pixelColor = backgroundImage.getPixel(j, i);
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255) // White
            {
                continue; // Skip white pixels
            }
            else if (red == 255 && green == 0 && blue == 128)
            {
                world.createEntity<Background>(j * 16, i * 16, 80, 80, 3, 0);
            }
            // else if (red == 34 && green == 177 && blue == 76)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 48, 20, 3, 1);
            // }
            // else if (red == 0 && green == 128 && blue == 0) // Big hill
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 80, 35, 3, 2);
            // }
            // else if (red == 195 && green == 195 && blue == 195)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 48, 24, 3, 3);
            // }
            // else if (red == 127 && green == 127 && blue == 127)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 64, 24, 3, 4);
            // }
            // else if (red == 0 && green == 0 && blue == 0)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 32, 24, 3, 5);
            // }
            // else if (red == 200 && green == 191 && blue == 231)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 32, 16, 3, 6);
            // }
            // else if (red == 255 && green == 174 && blue == 201)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 64, 16, 3, 7);
            // }
            // else if (red == 0 && green == 162 && blue == 232)
            // {
            //     world.createEntity<Background>(j * 16, i * 16, 48, 16, 3, 8);
            // }
            else if (red == 185 && green == 122 && blue == 87)
            {
                world.createEntity<Background>(j * 16, i * 16, 16, 162, 3, 9);
            }
        }
    }
}

void LevelHandler::start()
{
    setBackground();
    world.createEntity<SmallCoin>(325, 45, 15, 24);
    setLevel();
    setPlayer();
    setEnemy();
}