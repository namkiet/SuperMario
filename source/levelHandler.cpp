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
using namespace std;

LevelHandler::LevelHandler(Handler handler, UI *ui) : handler(handler), ui(ui)
{
    loadImage();
}

void LevelHandler::loadImage()
{
    levelImage = ui->getLevelImage();
    characterImage = ui->getCharacterImage();
}

void LevelHandler::setLevel()
{
    int width = levelImage.width;
    int height = levelImage.height;
    Color *pixels = LoadImageColors(levelImage);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = i * width + j;
            Color pixelColor = pixels[index];
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255) // White
            {
                continue; // Skip white pixels
            }
            else if (red == 0 && green == 0 && blue == 0) // Ground blocks
            {
                handler.addObject(new Block(j * 16, i * 16, 3, ui, BlockType::Ground));
            }
            else if (red == 128 && green == 255 && blue == 128) // Question blocks for coin
            {
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, QuestionBlockType::Coin));
            }
            else if (red == 128 && green == 128 && blue == 0) // Question blocks for mushroom
            {
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, QuestionBlockType::Mushroom));
            }
            else if (red == 239 && green == 116 && blue == 236) // Question blocks for flower
            {
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, QuestionBlockType::Flower));
            }
            else if (red == 242 && green == 234 && blue == 94) // Question blocks for star
            {
                handler.addObject(new QuestionBlock(j * 16, i * 16, 3, &handler, ui, QuestionBlockType::Star));
            }
            else if (red == 128 && green == 128 && blue == 255) // Normal blocks
            {
                handler.addObject(new NormalBlock(j * 16, i * 16, 3, ui));
            }
            else if (red == 0 && green == 128 && blue == 0) // Coin blocks
            {
                handler.addObject(new CoinBlock(j * 16, i * 16, 3, ui));
            }
            else if (red == 255 && green == 0 && blue == 128) // Stairs
            {
                handler.addObject(new Block(j * 16, i * 16, 3, ui, BlockType::Stairs));
            }
            else if (red == 255 && green == 128 && blue == 0) // Flag
            {
                handler.addObject(new Block(j * 16, i * 16, 3, ui));
            }
            else if (red == 255 && green == 128 && blue == 64) // Level-up block
            {
                handler.addObject(new Block(j * 16, i * 16, 3, ui, BlockType::LevelUp));
            }
            else if (red == 40 && green == 170 && blue == 170) // Star block
            {
                handler.addObject(new Block(j * 16, i * 16, 3, ui, BlockType::Star));
            }

            else if (red == 255 && green == 0 && blue == 0) // Nap cong
            {
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 0, 3, false, ui));
            }
            else if (red == 0 && green == 128 && blue == 255) // Normal pipes
            {
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, false, ui));
            }
            else if (red == 255 && green == 128 && blue == 128) // Go-in pipes
            {
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, true, ui));
            }
            else if (red == 185 && green == 122 && blue == 87) // Go-out pipes
            {
                handler.addObject(new Pipe(j * 16, i * 16, 32, 32, 1, 3, true, ui));
            }
        }
    }
    UnloadImageColors(pixels);
}

void LevelHandler::levelCharacter()
{
    int width = characterImage.width;
    int height = characterImage.height;
    Color *pixels = LoadImageColors(characterImage);
    bool playerSet = false;
    for (int j = 0; j < width && !playerSet; ++j)
    {
        for (int i = 0; i < height && !playerSet; ++i)
        {
            int index = i * width + j;
            Color pixelColor = pixels[index];
            int red = pixelColor.r;
            int green = pixelColor.g;
            int blue = pixelColor.b;

            if (red == 255 && green == 255 && blue == 255) // White
            {
                continue; // Skip white pixels
            }
            else if (red == 0 && green == 0 && blue == 0) // Black for player
            {
                // std::cout << "Player starting position found at: (" << j << ", " << i << ")" << std::endl;
                handler.setPlayer(*new Player(j * 16, i * 16, 0, 3, &handler, ui));
                playerSet = true;
            }
        }
    }
    UnloadImageColors(pixels);
}

void LevelHandler::start()
{
    setLevel();
    levelCharacter();
    setEnemy();
}

LevelHandler::~LevelHandler()
{
}

void LevelHandler::setEnemy()
{
    int width = characterImage.width;
    int height = characterImage.height;
    Color *pixels = LoadImageColors(characterImage);
    int count = 0;
    for (int j = 0; j < width; ++j)
    {
        for (int i = 0; i < height; ++i)
        {
            int index = i * width + j;
            Color pixelColor = pixels[index];
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
                    // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
                    handler.addObject(new Goomba(j * 16, i * 16, 0, 3, &handler, ui));
                }
            }
            else if (red == 255 && green == 174 && blue == 201)
            {
                if (count >= 1)
                {
                    // cout<< "Enemy starting position found at: (" << j << ", " << i << ")" << endl;
                    handler.addObject(new Koopa(j * 16, i * 16, 6, 3, &handler, ui));
                }
            }
            ++count;
        }
    }
    UnloadImageColors(pixels);
}