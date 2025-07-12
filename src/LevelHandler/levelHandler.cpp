#include <iostream>
#include "levelHandler.h"
#include "block.h"
#include "pipe.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include "questionBlock.h"
#include "normalBlock.h"
#include "coinBlock.h"
#include "starBlock.h"
#include "levelUpBlock.h"
#include "background.h"
using namespace std;

LevelHandler::LevelHandler(Handler handler, UI *ui, sf::RenderWindow &window) : handler(handler), ui(ui), window(window)
{
    if (this->ui == nullptr)
    {
        cerr << "UI is null in LevelHandler constructor!" << endl;
        return;
    }
    loadImage();
}

void LevelHandler::loadImage()
{
    levelImage = ui->getLevelImage();
    characterImage = ui->getCharacterImage();
    backgroundImage = ui->getBackgroundImage();
    if (levelImage.getSize().x == 0 || levelImage.getSize().y == 0)
    {
        cerr << "Failed to load level image!" << endl;
        return;
    }
    if (characterImage.getSize().x == 0 || characterImage.getSize().y == 0)
    {
        cerr << "Failed to load character image!" << endl;
        return;
    }
    if (backgroundImage.getSize().x == 0 || backgroundImage.getSize().y == 0)
    {
        cerr << "Failed to load background image!" << endl;
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
                handler.addObject(new Block(j * 16, i * 16, 3, ui, window, BlockType::Ground));
                // cout << "Ground block added" << endl;
            }
            else if (red == 128 && green == 255 && blue == 128) // Question blocks for coin
            {
                // cout << "Before adding question block" << endl;
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, window, QuestionBlockType::Coin));
                // cout << "Coin question block added" << endl;
            }
            else if (red == 128 && green == 128 && blue == 0) // Question blocks for mushroom
            {
                // cout << "Before adding mushroom question block" << endl;
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, window, QuestionBlockType::Mushroom));
                // cout << "Mushroom question block added" << endl;
            }
            else if (red == 239 && green == 116 && blue == 236) // Question blocks for flower
            {
                // cout << "Before adding flower question block" << endl;
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, window, QuestionBlockType::Flower));
                // cout << "Flower question block added" << endl;
            }
            else if (red == 242 && green == 234 && blue == 94) // Question blocks for star
            {
                // cout << "Before adding star question block" << endl;
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, window, QuestionBlockType::Star));
                // cout << "Star question block added" << endl;
            }
            else if (red == 128 && green == 128 && blue == 255) // Normal blocks
            {
                // cout << "Before adding normal block" << endl;
                handler.addObject(new NormalBlock(j * 16, i * 16, 3, ui, window));
                // cout << "Normal block added" << endl;
            }
            else if (red == 0 && green == 128 && blue == 0) // Coin blocks
            {
                // cout << "Before adding coin block" << endl;
                handler.addObject(new CoinBlock(j * 16, i * 16, 3, ui, window));
                // cout << "Coin block added" << endl;
            }
            else if (red == 255 && green == 0 && blue == 128) // Stairs
            {
                // cout << "Before adding stairs block" << endl;
                handler.addObject(new Block(j * 16, i * 16, 3, ui, window, BlockType::Stairs));
                // cout << "Stairs block added" << endl;
            }
            else if (red == 255 && green == 128 && blue == 64) // Level-up block
            {
                // cout << "Before adding level-up block" << endl;
                handler.addObject(new LevelUpBlock(j * 16, i * 16, 3, &handler, ui, window));
                // cout << "Level-up block added" << endl;
            }
            else if (red == 40 && green == 170 && blue == 170) // Star block
            {
                // cout << "Before adding star block" << endl;
                handler.addObject(new StarBlock(j * 16, i * 16, 3, &handler, ui, window));
                // cout << "Star block added" << endl;
            }
            else if (red == 255 && green == 0 && blue == 0) // Nap cong
            {
                // cout << "Before adding pipe block" << endl;
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 0, 3, false, ui, window));
                // cout << "Pipe block added" << endl;
            }
            else if (red == 0 && green == 128 && blue == 255) // Normal pipes
            {
                // cout << "Before adding normal pipe block" << endl;
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, false, ui, window));
                // cout << "Normal pipe added" << endl;
            }
            else if (red == 255 && green == 128 && blue == 128) // Go-in pipes
            {
                // cout << "Before adding go-in pipe block" << endl;
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, true, ui, window));
                // cout << "Go-in pipe added" << endl;
            }
            else if (red == 185 && green == 122 && blue == 87) // Go-out pipes
            {
                // cout << "Before adding go-out pipe block" << endl;
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, true, ui, window));
                // cout << "Go-out pipe added" << endl;
            }
            else if (red == 163 && green == 73 && blue == 164)
            {
                // cout << "Before adding flag block" << endl;
                handler.addObject(new Block(j * 16, i * 16, 3, ui, window, BlockType::Flag));
                // cout << "Flag block added" << endl;
            }
        }
    }
}

void LevelHandler::levelCharacter()
{
    int width = characterImage.getSize().x;
    int height = characterImage.getSize().y;
    bool playerSet = false;
    for (int j = 0; j < width && !playerSet; ++j)
    {
        for (int i = 0; i < height && !playerSet; ++i)
        {

            sf::Color pixelColor = characterImage.getPixel(j, i);
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
                handler.setPlayer(*new Player(j * 16, i * 16, 3, &handler, ui, window, PlayerID::Luigi, PlayerType::Normal, PlayerState::Small));
                playerSet = true;
            }
        }
    }
}

void LevelHandler::start()
{

    setBackground();

    setLevel();
    // cout << "In LevelHandler::start()" << endl;
    levelCharacter();
    setEnemy();
}

LevelHandler::~LevelHandler()
{
}

void LevelHandler::setEnemy()
{
    int width = characterImage.getSize().x;
    int height = characterImage.getSize().y;
    int count = 0;
    for (int j = 0; j < width; ++j)
    {
        for (int i = 0; i < height; ++i)
        {

            sf::Color pixelColor = characterImage.getPixel(j, i);
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
                    handler.addObject(new Goomba(j * 16, i * 16, 3, &handler, ui, window));
                }
            }
            else if (red == 255 && green == 174 && blue == 201)
            {
                if (count >= 1)
                {
                    // // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
                    handler.addObject(new Koopa(j * 16, i * 16, 3, &handler, ui, window));
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
            else if (red == 0 && green == 128 && blue == 0) // Big hill
            {
                handler.addObject(new BackGround(j * 16, i * 16, 80, 35, 3, ui, window, BackGroundType::BigHill));
            }
            else if (red == 34 && green == 177 && blue == 76)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 48, 20, 3, ui, window, BackGroundType::SmallHill));
            }
            else if (red == 200 && green == 191 && blue == 231)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 32, 16, 3, ui, window, BackGroundType::Plant1));
            }
            else if (red == 0 && green == 162 && blue == 232)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 48, 16, 3, ui, window, BackGroundType::Plant2));
            }
            else if (red == 255 && green == 174 && blue == 201)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 64, 16, 3, ui, window, BackGroundType::Plant3));
            }
            else if (red == 0 && green == 0 && blue == 0)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 32, 24, 3, ui, window, BackGroundType::Cloud1));
            }
            else if (red == 195 && green == 195 && blue == 195)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 48, 24, 3, ui, window, BackGroundType::Cloud2));
            }
            else if (red == 127 && green == 127 && blue == 127)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 64, 24, 3, ui, window, BackGroundType::Cloud3));
            }
            else if (red == 255 && green == 0 && blue == 128)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 80, 80, 3, ui, window, BackGroundType::Castle));
            }
            else if (red == 185 && green == 122 && blue == 87)
            {
                handler.addObject(new BackGround(j * 16, i * 16, 16, 162, 3, ui, window, BackGroundType::FlagPole));
            }
        }
    }
}