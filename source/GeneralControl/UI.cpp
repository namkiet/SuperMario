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

void UI::getLargePlayerTextures()
{
    int x_off = 80;
    int y_off = 1;
    int width = 16;
    int height = 32;

    // Large Mario
    for (int j = 0; j < 7; ++j)
    {
        for (int i = 0; i < MARIO_L_COUNT; ++i)
        {
            Rectangle cropRect = {x_off + i * (width + 1),
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(player_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);

            if (j == 0)
                marioLarge[i] = texture;
            else if (j == 1)
                luigiLarge[i] = texture; // Luigi textures
            else if (j == 2)
                marioLargeFire[i] = texture;
            else if (j == 3)
                marioLargeRed[i] = texture;
            else if (j == 4)
                marioLargeBlack[i] = texture;
            else if (j == 5)
                marioLargeGreen[i] = texture;
            else if (j == 6)
                marioLargeBlue[i] = texture;
        }
        if (j == 0)
            y_off += height * 2 + 1;
        else if (j == 1 || j == 2 || j == 3 || j == 4 || j == 5)
            y_off += height * 2 - 1;
    }
}

void UI::getSmallPlayerTextures()
{
    int x_off = 80;
    int y_off = 34;
    int width = 16;
    int height = 16;
    for (int j = 0; j < 7; ++j)
    {
        for (int i = 0; i < MARIO_S_COUNT; ++i)
        {
            Rectangle cropRect = {x_off + i * (width + 1),
                                  y_off,
                                  width,
                                  height};
            Image cropped = ImageFromImage(player_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
                marioSmall[i] = texture; // Mario small textures
            else if (j == 1)
                luigiSmall[i] = texture; // Luigi small textures
            else if (j == 2)
                marioSmallFire[i] = texture;
            else if (j == 3)
                marioSmallRed[i] = texture;
            else if (j == 4)
                marioSmallBlack[i] = texture;
            else if (j == 5)
                marioSmallGreen[i] = texture;
            else if (j == 6)
                marioSmallBlue[i] = texture;
        }
        if (j == 0)
            y_off += height * 4 + 1;
        else if (j == 1 || j == 2 || j == 3 || j == 4 || j == 5)
            y_off += height * 4 - 1;
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
           player_sheet{nullptr}, enemy_sheet{nullptr}, block_sheet{nullptr}, npc_sheet{nullptr},
           background_sheet{nullptr}, background_sheet2{nullptr}
{
}

void UI::loadImages()
{
    player_sheet = LoadImage(RES_PATH "Sprites/character.png");
    enemy_sheet = LoadImage(RES_PATH "Sprites/enemies.png");
    npc_sheet = LoadImage(RES_PATH "Sprites/item.png");
    block_sheet = LoadImage(RES_PATH "Sprites/block.png");
    tile_sheet = LoadImage(RES_PATH "Sprites/tileset.png");
    fire_sheet = LoadImage(RES_PATH "Sprites/fire.png");
    background_sheet = LoadImage(RES_PATH "Sprites/background.png");
    background_sheet2 = LoadImage(RES_PATH "Sprites/background2.png");

    levelImage = LoadImage(RES_PATH "Levels/map11.png");
    backgroundImage = LoadImage(RES_PATH "Levels/map11b.png");
    characterImage = LoadImage(RES_PATH "Levels/map11c.png");

    getLargePlayerTextures();
    getSmallPlayerTextures();
    getTileTextures();
    getPipeTextures();
    getDebrisTextures();
    getEnemyTextures();
    getItemTextures();
    getFireBulletTextures();
    getBackgroundTextures();
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
    UnloadImage(backgroundImage);

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
    for (auto &texture : coin1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : coin2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : coin3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : coin4)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : mushroom1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : mushroom2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : mushroom3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : mushroom4)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : flower1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : flower2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : flower3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : flower4)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : star1)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : star2)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : star3)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : star4)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioLargeFire)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioLargeRed)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioLargeBlack)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioLargeGreen)
    {
        UnloadTexture(texture);
    }
    for (auto &texture : marioLargeBlue)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : luigiLarge)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : luigiSmall)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : marioSmallFire)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : marioSmallRed)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : marioSmallBlack)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : marioSmallGreen)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : marioSmallBlue)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : fireBullet)
    {
        UnloadTexture(texture);
    }

    for (auto &texture : backgroundTextures)
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
    int y_off = 16;
    int width = 16;
    int height = 16;

    // Get the normal mushroom
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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

    // Get the stomped mushroom
    x_off = 32;
    y_off = 24;
    height = 8;
    width = 16;
    for (int j = 0; j < 4; ++j)
    {
        Rectangle cropRect = {x_off,
                              y_off * (j + 1) + j * height,
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
            enemy1[2] = texture; // Stomped enemy1
        }
        else if (j == 1)
        {
            enemy2[2] = texture; // Stomped enemy2
        }
        else if (j == 2)
        {
            enemy3[2] = texture; // Stomped enemy3
        }
        else if (j == 3)
        {
            enemy4[2] = texture; // Stomped enemy4
        }
    }

    // For normal and flying koopa
    x_off = 96;
    y_off = 8;
    height = 24;
    width = 16;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 3] = texture; // Normal koopa
            }
            else if (j == 1)
            {
                enemy2[i + 3] = texture; // Normal koopa
            }
            else if (j == 2)
            {
                enemy3[i + 3] = texture; // Flying koopa
            }
            else if (j == 3)
            {
                enemy4[i + 3] = texture; // Flying koopa
            }
        }
    }

    // For stomped koopa without legs
    x_off = 161;
    y_off = 17;
    height = 12;
    width = 14;

    for (int j = 0; j < 4; ++j)
    {
        Rectangle cropRect = {x_off,
                              y_off * (j + 1) + j * height,
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
            enemy1[7] = texture; // Stomped koopa without legs
        }
        else if (j == 1)
        {
            enemy2[7] = texture; // Stomped koopa without legs
        }
        else if (j == 2)
        {
            enemy3[7] = texture; // Stomped koopa without legs
        }
        else if (j == 3)
        {
            enemy4[7] = texture; // Stomped koopa without legs
        }
    }

    // For stomped koopa with legs
    x_off = 177;
    y_off = 17;
    height = 16;
    width = 14;

    for (int j = 0; j < 4; ++j)
    {
        Rectangle cropRect = {x_off,
                              y_off * (j + 1) + j * height,
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
            enemy1[8] = texture; // Stomped koopa with legs
        }
        else if (j == 1)
        {
            enemy2[8] = texture; // Stomped koopa with legs
        }
        else if (j == 2)
        {
            enemy3[8] = texture; // Stomped koopa with legs
        }
        else if (j == 3)
        {
            enemy4[8] = texture; // Stomped koopa with legs
        }
    }

    // For upright plants
    x_off = 192;
    y_off = 8;
    height = 25;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 9] = texture; // Upright plant
            }
            else if (j == 1)
            {
                enemy2[i + 9] = texture; // Upright plant
            }
            else if (j == 2)
            {
                enemy3[i + 9] = texture; // Upright plant
            }
            else if (j == 3)
            {
                enemy4[i + 9] = texture; // Upright plant
            }
        }
    }

    // For inverted plants
    x_off = 256;
    y_off = 8;
    height = 25;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 11] = texture; // Inverted plant
            }
            else if (j == 1)
            {
                enemy2[i + 11] = texture; // Inverted plant
            }
            else if (j == 2)
            {
                enemy3[i + 11] = texture; // Inverted plant
            }
            else if (j == 3)
            {
                enemy4[i + 11] = texture; // Inverted plant
            }
        }
    }

    // For monkey
    x_off = 320;
    y_off = 8;
    height = 24;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 13] = texture; // Monkey
            }
            else if (j == 1)
            {
                enemy2[i + 13] = texture; // Monkey
            }
            else if (j == 3)
            {
                enemy4[i + 13] = texture; // Monkey
            }
        }
    }

    // For sun
    x_off = 416;
    y_off = 8;
    height = 24;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 17] = texture; // Sun
            }
            else if (j == 1)
            {
                enemy2[i + 17] = texture; // Sun
            }
            else if (j == 2)
            {
                enemy3[i + 17] = texture; // Sun
            }
            else if (j == 3)
            {
                enemy4[i + 17] = texture; // Sun
            }
        }
    }

    // For hedgehog and bullets
    x_off = 512;
    y_off = 16;
    height = 16;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 19] = texture; // Hedgehog
            }
            else if (j == 1)
            {
                enemy2[i + 19] = texture; // Hedgehog
            }
            else if (j == 2)
            {
                enemy3[i + 19] = texture; // Bullet
            }
            else if (j == 3)
            {
                enemy4[i + 19] = texture; // Bullet
            }
        }
    }

    // For stomped jellyfish
    x_off = 592;
    y_off = 8;
    height = 16;
    width = 16;
    for (int j = 0; j < 4; ++j)
    {
        Rectangle cropRect = {x_off,
                              y_off * (j + 1) + j * height,
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
            enemy1[23] = texture; // Jellyfish
        }
        else if (j == 1)
        {
            enemy2[23] = texture; // Jellyfish
        }
        else if (j == 2)
        {
            enemy3[23] = texture; // Jellyfish
        }
        else if (j == 3)
        {
            enemy4[23] = texture; // Jellyfish
        }
    }

    // For jellyfish
    x_off = 608;
    y_off = 8;
    height = 24;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        Rectangle cropRect = {x_off,
                              y_off * (j + 1) + j * height,
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
            enemy1[24] = texture; // Jellyfish
        }
        else if (j == 1)
        {
            enemy2[24] = texture; // Jellyfish
        }
        else if (j == 2)
        {
            enemy3[24] = texture; // Jellyfish
        }
        else if (j == 3)
        {
            enemy4[24] = texture; // Jellyfish
        }
    }

    // For cheep cheep
    x_off = 624;
    y_off = 16;
    height = 16;
    width = 16;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            Rectangle cropRect = {x_off + i * (width),
                                  y_off * (j + 1) + j * height,
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
                enemy1[i + 25] = texture; // Cheep cheep
            }
            else if (j == 1)
            {
                enemy2[i + 25] = texture; // Cheep cheep
            }
            else if (j == 2)
            {
                enemy3[i + 25] = texture; // Cheep cheep
            }
            else if (j == 3)
            {
                enemy4[i + 25] = texture; // Cheep cheep
            }
        }
    }

    // For dragon
    x_off = 656;
    y_off = 0;
    height = 32;
    width = 32;

    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
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
                enemy1[i + 27] = texture; // Dragon
            }
            else if (j == 1)
            {
                enemy2[i + 27] = texture; // Dragon
            }
            else if (j == 2)
            {
                enemy3[i + 27] = texture; // Dragon
            }
            else if (j == 3)
            {
                enemy4[i + 27] = texture; // Dragon
            }
        }
    }
}

std::vector<Texture2D> &UI::getCoin1()
{
    return coin1;
}

std::vector<Texture2D> &UI::getCoin2()
{
    return coin2;
}

std::vector<Texture2D> &UI::getCoin3()
{
    return coin3;
}

std::vector<Texture2D> &UI::getCoin4()
{
    return coin4;
}

std::vector<Texture2D> &UI::getMushroom1()
{
    return mushroom1;
}

std::vector<Texture2D> &UI::getMushroom2()
{
    return mushroom2;
}

std::vector<Texture2D> &UI::getMushroom3()
{
    return mushroom3;
}

std::vector<Texture2D> &UI::getMushroom4()
{
    return mushroom4;
}

std::vector<Texture2D> &UI::getFlower1()
{
    return flower1;
}

std::vector<Texture2D> &UI::getFlower2()
{
    return flower2;
}

std::vector<Texture2D> &UI::getFlower3()
{
    return flower3;
}

std::vector<Texture2D> &UI::getFlower4()
{
    return flower4;
}

std::vector<Texture2D> &UI::getStar1()
{
    return star1;
}

std::vector<Texture2D> &UI::getStar2()
{
    return star2;
}

std::vector<Texture2D> &UI::getStar3()
{
    return star3;
}

std::vector<Texture2D> &UI::getStar4()
{
    return star4;
}

void UI::getItemTextures()
{
    int x_off = 0;
    int y_off = 0;
    int width = 16;
    int height = 16;

    // For mushrooms
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            x_off += 9 * width * j;

            Rectangle cropRect = {x_off + i * (width),
                                  y_off,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > npc_sheet.width || cropRect.y + cropRect.height > npc_sheet.height)
            {
                continue;
            }
            Image cropped = ImageFromImage(npc_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                mushroom1[i] = texture;
            }
            else if (j == 1)
            {
                mushroom2[i] = texture;
            }
            else if (j == 2)
            {
                mushroom3[i] = texture;
            }
            else if (j == 3)
            {
                mushroom4[i] = texture;
            }
        }
    }

    x_off = 0;
    y_off += width * 2;

    // For flowers
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            x_off += 9 * width * j;
            Rectangle cropRect = {x_off + i * (width),
                                  y_off,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > npc_sheet.width || cropRect.y + cropRect.height > npc_sheet.height)
            {
                continue;
            }
            Image cropped = ImageFromImage(npc_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                flower1[i] = texture;
            }
            else if (j == 1)
            {
                flower2[i] = texture;
            }
            else if (j == 2)
            {
                flower3[i] = texture;
            }
            else if (j == 3)
            {
                flower4[i] = texture;
            }
        }
    }

    x_off = 0;
    y_off += width;

    // For stars
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            x_off += 9 * width * j;
            Rectangle cropRect = {x_off + i * (width),
                                  y_off,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > npc_sheet.width || cropRect.y + cropRect.height > npc_sheet.height)
            {
                continue;
            }
            Image cropped = ImageFromImage(npc_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                star1[i] = texture;
            }
            else if (j == 1)
            {
                star2[i] = texture;
            }
            else if (j == 2)
            {
                star3[i] = texture;
            }
            else if (j == 3)
            {
                star4[i] = texture;
            }
        }
    }

    x_off = 0;
    y_off += width * 3;

    // For coins
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            x_off += 9 * width * j;
            Rectangle cropRect = {x_off + i * (width),
                                  y_off,
                                  width,
                                  height};
            if (cropRect.x + cropRect.width > npc_sheet.width || cropRect.y + cropRect.height > npc_sheet.height)
            {
                continue;
            }
            Image cropped = ImageFromImage(npc_sheet, cropRect);
            Texture2D texture = LoadTextureFromImage(cropped);
            UnloadImage(cropped);
            if (j == 0)
            {
                coin1[i] = texture;
            }
            else if (j == 1)
            {
                coin2[i] = texture;
            }
            else if (j == 2)
            {
                coin3[i] = texture;
            }
            else if (j == 3)
            {
                coin4[i] = texture;
            }
        }
    }
}

std::vector<Texture2D> &UI::getLuigiLarge()
{
    return luigiLarge;
}

std::vector<Texture2D> &UI::getLuigiSmall()
{
    return luigiSmall;
}

std::vector<Texture2D> &UI::getFireLarge()
{
    return marioLargeFire;
}
std::vector<Texture2D> &UI::getRedLarge()
{
    return marioLargeRed;
}
std::vector<Texture2D> &UI::getBlackLarge()
{
    return marioLargeBlack;
}

std::vector<Texture2D> &UI::getGreenLarge()
{
    return marioLargeGreen;
}

std::vector<Texture2D> &UI::getBlueLarge()
{
    return marioLargeBlue;
}

std::vector<Texture2D> &UI::getFireSmall()
{
    return marioSmallFire;
}

std::vector<Texture2D> &UI::getRedSmall()
{
    return marioSmallRed;
}

std::vector<Texture2D> &UI::getBlackSmall()
{
    return marioSmallBlack;
}

std::vector<Texture2D> &UI::getGreenSmall()
{
    return marioSmallGreen;
}

std::vector<Texture2D> &UI::getBlueSmall()
{
    return marioSmallBlue;
}

void UI::loadAudio()
{
    // Load music for longer audio files
    overWorldBackGround = LoadMusicStream(RES_PATH "Sounds/Background.mp3");
    gameOver = LoadMusicStream(RES_PATH "Sounds/gameover.wav");

    // Load sound effects for shorter audio files
    levelUp = LoadSound(RES_PATH "Sounds/1up.wav");
    powerUp = LoadSound(RES_PATH "Sounds/powerup.wav");
}

void UI::unloadAudio()
{
    UnloadMusicStream(overWorldBackGround);
    UnloadMusicStream(gameOver);

    UnloadSound(levelUp);
    UnloadSound(powerUp);
}

Music &UI::getOverworldBackGroundMusic()
{
    return overWorldBackGround;
}

Music &UI::getGameOverMusic()
{
    return gameOver;
}

Sound &UI::getLevelUpSound()
{
    return levelUp;
}

Sound &UI::getPowerUpSound()
{
    return powerUp;
}

void UI::getFireBulletTextures()
{
    int x_off = 189;
    int y_off = 240;
    int width = 8;
    int height = 8;

    for (int i = 0; i < 4; ++i)
    {
        Rectangle cropRect = {x_off + i * 35,
                              y_off,
                              width,
                              height};
        Image cropped = ImageFromImage(fire_sheet, cropRect);
        Texture2D texture = LoadTextureFromImage(cropped);
        UnloadImage(cropped);
        fireBullet[i] = texture;
    }

    x_off = 395;
    y_off = 236;
    width = 16;
    height = 16;
    Rectangle cropRect = {x_off,
                          y_off,
                          width,
                          height};
    Image cropped = ImageFromImage(fire_sheet, cropRect);
    Texture2D texture = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    fireBullet[4] = texture;
}

std::vector<Texture2D> &UI::getFireBullet()
{
    return fireBullet;
}

void UI::getBackgroundTextures()
{
    int x_off = 272;
    int y_off = 218;
    int width = 80;
    int height = 80;

    Rectangle cropRect = {x_off,
                          y_off,
                          width,
                          height};
    Image cropped = ImageFromImage(background_sheet, cropRect);
    Texture2D texture = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    backgroundTextures[0] = texture;

    x_off = 48;
    y_off = 176;
    width = 48;
    height = 20;
    Rectangle cropRect1 = {x_off,
                           y_off,
                           width,
                           height};
    cropped = ImageFromImage(background_sheet, cropRect1);
    texture = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    backgroundTextures[1] = texture;
    
    x_off = 99;
    y_off = 160;
    width = 80;
    height = 35;
    Rectangle cropRect2 = {x_off,
                           y_off,
                           width,
                           height};
    cropped = ImageFromImage(background_sheet, cropRect2);
    texture = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    backgroundTextures[2] = texture;

    x_off = 46;
    y_off = 198;
    width = 48;
    height = 24;
    for (int i = 3; i < 6; ++i)
    {
        Rectangle cropRect3 = {x_off,
                               y_off,
                               width,
                               height};
        cropped = ImageFromImage(background_sheet, cropRect3);
        texture = LoadTextureFromImage(cropped);
        UnloadImage(cropped);
        backgroundTextures[i] = texture;

        if (i == 3)
        {
            x_off = 96;
            width = 64;
        }
        else if (i == 4)
        {
            x_off = 162;
            width = 32;
        }
    }

    x_off = 51;
    y_off = 253;
    width = 32;
    height = 16;
    for (int i = 6; i < 9; ++i)
    {
        Rectangle cropRect4 = {x_off,
                               y_off,
                               width,
                               height};
        cropped = ImageFromImage(background_sheet, cropRect4);
        texture = LoadTextureFromImage(cropped);
        UnloadImage(cropped);
        backgroundTextures[i] = texture;

        if (i == 6)
        {
            x_off = 85;
            width = 64;
        }
        else if (i == 7)
        {
            x_off = 151;
            width = 48;
        }
    }

    x_off = 70;
    y_off = 31;
    width = 16;
    height = 325;
    Rectangle cropRect5 = {x_off,
                           y_off,
                           width,
                           height};
    cropped = ImageFromImage(background_sheet2, cropRect5);
    texture = LoadTextureFromImage(cropped);
    UnloadImage(cropped);
    backgroundTextures[9] = texture;
}

std::vector<Texture2D> &UI::getBackground()
{
    return backgroundTextures;
}

Image &UI::getBackgroundImage()
{
    return backgroundImage;
}