#include <iostream>
#include "UI.h"
using namespace std;

vector<Texture2D> &UI::getMarioLarge()
{
    return marioLarge;
}
vector<Texture2D> &UI::getMarioSmall()
{
    return marioSmall;
}
vector<Texture2D> &UI::getTile1()
{
    return tile1;
}
vector<Texture2D> &UI::getTile2()
{
    return tile2;
}
vector<Texture2D> &UI::getTile3()
{
    return tile3;
}
vector<Texture2D> &UI::getTile4()
{
    return tile4;
}
vector<Texture2D> &UI::getPipe1()
{
    return pipe1;
}

UI::~UI()
{
}

void UI::getPlayerTextures()
{
    int x_off = 80;
    int y_off = 1;
    int width = 16;
    int height = 32;
    for (int i = 0; i < MARIO_L_COUNT; ++i)
    {
        Rectangle cropRect = {x_off + i * (width + 1),
                              y_off,
                              width,
                              height};
        Image cropped = ImageFromImage(player_sheet, cropRect);
        Texture2D texture = LoadTextureFromImage(cropped);
        UnloadImage(cropped);

        marioLarge[i] = texture;
    }

    y_off += height + 1;
    height = 16;
    for (int i = 0; i < MARIO_S_COUNT; ++i)
    {
        Rectangle cropRect = {x_off + i * (width + 1),
                              y_off,
                              width,
                              height};
        Image cropped = ImageFromImage(player_sheet, cropRect);
        Texture2D texture = LoadTextureFromImage(cropped);
        UnloadImage(cropped);
        marioSmall[i] = texture;
    }
}

void UI::getTileTextures()
{
    int x_off = 0;
    int y_off = 0;
    int width = 16;
    int height = 16;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < TILE_1_COUNT; ++i)
        {

            Rectangle cropRect = {x_off + i * (width),
                                  y_off + j * height * 2,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > tile_sheet.width || cropRect.y + cropRect.height > tile_sheet.height)
            {
                // cout << "Image from image width = " << title_sheet.width << ", height = " << title_sheet.height << endl;
                // cout << "cropRect width = " << cropRect.width + cropRect.x << ", height = " << cropRect.height + cropRect.y << endl;
                continue;
            }
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                tile1[i] = texture;
            }
            else if (j == 1)
            {
                tile2[i] = texture;
            }
            else if (j == 2)
            {

                tile3[i] = texture;
            }
            else if (j == 3)
            {
                tile4[i] = texture;
            }
        }
        y_off += height;
        for (int i = 0; i < TILE_2_COUNT; ++i)
        {

            Rectangle cropRect = {x_off + i * (width),
                                  y_off + j * height * 2,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > tile_sheet.width || cropRect.y + cropRect.height > tile_sheet.height)
            {
                // cout << "Image from image width = " << title_sheet.width << ", height = " << title_sheet.height << endl;
                // cout << "cropRect width = " << cropRect.width + cropRect.x << ", height = " << cropRect.height + cropRect.y << endl;
                continue;
            }
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {

                tile1[i + TILE_1_COUNT] = texture;
            }
            else if (j == 1)
            {
                tile2[i + TILE_1_COUNT] = texture;
            }
            else if (j == 2)
            {

                tile3[i + TILE_1_COUNT] = texture;
            }
            else if (j == 3)
            {
                tile4[i + TILE_1_COUNT] = texture;
            }
        }
    }
}

void UI::getPipeTextures()
{
    int x_off = 0;
    int y_off = 16 * 8;
    int width = 32;
    int height = 16;
    for (int i = 0; i < 4; ++i)
    {
        Texture2D texture;
        if (i == 0)
        {
            Rectangle cropRect = {x_off,
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else if (i == 1)
        {
            Rectangle cropRect = {x_off,
                                  y_off + height,
                                  width,
                                  height};
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else if (i == 2)
        {
            Rectangle cropRect = {x_off + width,
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else
        {
            Rectangle cropRect = {x_off + width,
                                  y_off + height,
                                  width,
                                  height};
            Image cropped = ImageFromImage(tile_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        pipe1[i] = texture;
    }
}

UI::UI() : tile_sheet{nullptr}, game_over_sheet{nullptr}, intro_sheet{nullptr},
           player_sheet{nullptr}, enemy_sheet{nullptr}, block_sheet{nullptr}, npc_sheet{nullptr}
{
}

void UI::loadImages()
{
    player_sheet = LoadImage(RES_PATH "character.png");
    enemy_sheet = LoadImage(RES_PATH "enemies.png");
    npc_sheet = LoadImage(RES_PATH "item.jpg");
    block_sheet = LoadImage(RES_PATH "block.png");
    tile_sheet = LoadImage(RES_PATH "tileset.png");

    levelImage = LoadImage(RES_PATH "map11.png");
    characterImage = LoadImage(RES_PATH "map11c.png");

    getPlayerTextures();
    getTileTextures();
    getPipeTextures();
    getDebrisTextures();
    getEnemyTextures();
}

void UI::unloadImages()
{

    UnloadImage(player_sheet);
    UnloadImage(enemy_sheet);
    UnloadImage(block_sheet);
    UnloadImage(npc_sheet);
    UnloadImage(tile_sheet);
    UnloadImage(game_over_sheet);
    UnloadImage(intro_sheet);

    UnloadImage(levelImage);
    UnloadImage(characterImage);

    for (auto &texture : marioLarge)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioSmall)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : tile1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : tile2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : tile3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : tile4)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : pipe1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : debris1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : enemy1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : enemy2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : enemy3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : enemy4)
    {
        UnloadTexture(texture);
    }
}

Image &UI::getLevelImage()
{
    return levelImage;
}

Image &UI::getCharacterImage()
{
    return characterImage;
}

vector<Texture2D> &UI::getDebris1()
{
    return debris1;
}

void UI::getDebrisTextures()
{
    int x_off = 304;
    int y_off = 112;
    int width = 8;
    int height = 8;
    for (int i = 0; i < 4; ++i)
    {
        Texture2D texture;
        if (i == 0)
        {
            Rectangle cropRect = {x_off,
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(block_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else if (i == 1)
        {
            Rectangle cropRect = {x_off,
                                  y_off + height,
                                  width,
                                  height};
            Image cropped = ImageFromImage(block_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else if (i == 2)
        {
            Rectangle cropRect = {x_off + width,
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(block_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        else
        {
            Rectangle cropRect = {x_off + width,
                                  y_off + height,
                                  width,
                                  height};
            Image cropped = ImageFromImage(block_sheet, cropRect);
            texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
        }
        debris1[i] = texture;
    }
}

std::vector<Texture2D> &UI::getEnemy1()
{
    return enemy1;
}

std::vector<Texture2D> &UI::getEnemy2()
{
    return enemy2;
}

std::vector<Texture2D> &UI::getEnemy3()
{
    return enemy3;
}

std::vector<Texture2D> &UI::getEnemy4()
{
    return enemy4;
}

void UI::getEnemyTextures()
{
    int x_off = 0;
    int y_off = 0;
    int width = 16;
    int height = 32;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < ENEMY_COUNT; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off + j * height,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > enemy_sheet.width || cropRect.y + cropRect.height > enemy_sheet.height)
            {
                continue;
            }
            Image cropped = ImageFromImage(enemy_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                enemy1[i] = texture;
            }
            else if (j == 1)
            {
                enemy2[i] = texture;
            }
            else if (j == 2)
            {
                enemy3[i] = texture;
            }
            else if (j == 3)
            {
                enemy4[i] = texture;
            }
        }
    }
}
