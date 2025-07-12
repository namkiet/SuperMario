#include <iostream>
#include "UI.h"
using namespace std;

vector<sf::Texture> &UI::getMarioLarge()
{
    return marioLarge;
}
vector<sf::Texture> &UI::getMarioSmall()
{
    return marioSmall;
}
vector<sf::Texture> &UI::getTile1()
{
    return tile1;
}
vector<sf::Texture> &UI::getTile2()
{
    return tile2;
}
vector<sf::Texture> &UI::getTile3()
{
    return tile3;
}
vector<sf::Texture> &UI::getTile4()
{
    return tile4;
}
vector<sf::Texture> &UI::getPipe1()
{
    return pipe1;
}

UI::~UI()
{
}

void UI::getLargePlayerTextures()
{
    // cout << "In UI::getLargePlayerTextures()" << endl;
    int x_off = 80;
    int y_off = 1;
    int width = 16;
    int height = 32;

    // Large Mario
    for (int j = 0; j < 7; ++j)
    {
        for (int i = 0; i < MARIO_L_COUNT; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width + 1), y_off, width, height);
            sf::Texture texture;
            texture.loadFromImage(player_sheet, cropRect);

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
    // cout << "In UI::getSmallPlayerTextures()" << endl;
    int x_off = 80;
    int y_off = 34;
    int width = 16;
    int height = 16;
    for (int j = 0; j < 7; ++j)
    {
        for (int i = 0; i < MARIO_S_COUNT; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width + 1), y_off, width, height);
            sf::Texture texture;
            texture.loadFromImage(player_sheet, cropRect);

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
    // cout << "In UI::getTileTextures()" << endl;
    int x_off = 0;
    int y_off = 0;
    int width = 16;
    int height = 16;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < TILE_1_COUNT; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width), y_off + j * height * 2, width, height);
            sf::Texture texture;
            texture.loadFromImage(tile_sheet, cropRect);

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

            sf::IntRect cropRect(x_off + i * (width), y_off + j * height * 2, width, height);
            sf::Texture texture;
            texture.loadFromImage(tile_sheet, cropRect);

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
    // cout << "In UI::getPipeTextures()" << endl;
    int x_off = 0;
    int y_off = 16 * 8;
    int width = 32;
    int height = 16;
    for (int i = 0; i < 4; ++i)
    {
        sf::Texture texture;
        if (i == 0)
        {
            sf::IntRect cropRect(x_off, y_off, width, height);
            texture.loadFromImage(tile_sheet, cropRect);
        }
        else if (i == 1)
        {
            sf::IntRect cropRect(x_off, y_off + height, width, height);
            texture.loadFromImage(tile_sheet, cropRect);
        }
        else if (i == 2)
        {
            sf::IntRect cropRect(x_off + width, y_off, width, height);
            texture.loadFromImage(tile_sheet, cropRect);
        }
        else
        {
            sf::IntRect cropRect(x_off + width, y_off + height, width, height);
            texture.loadFromImage(tile_sheet, cropRect);
        }
        pipe1[i] = texture;
    }
}

UI::UI()
{
}

void UI::loadImages()
{
    player_sheet.loadFromFile("assets/Sprites/character.png");
    enemy_sheet.loadFromFile("assets/Sprites/enemies.png");
    npc_sheet.loadFromFile("assets/Sprites/item.png");
    block_sheet.loadFromFile("assets/Sprites/block.png");
    tile_sheet.loadFromFile("assets/Sprites/tileset.png");
    fire_sheet.loadFromFile("assets/Sprites/fire.png");
    background_sheet.loadFromFile("assets/Sprites/background.png");
    background_sheet2.loadFromFile("assets/Sprites/background2.png");

    levelImage.loadFromFile("assets/Levels/map11.png");
    backgroundImage.loadFromFile("assets/Levels/map11b.png");
    characterImage.loadFromFile("assets/Levels/map11c.png");

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

sf::Image &UI::getLevelImage()
{
    return levelImage;
}

sf::Image &UI::getCharacterImage()
{
    return characterImage;
}

vector<sf::Texture> &UI::getDebris1()
{
    return debris1;
}

void UI::getDebrisTextures()
{
    // cout << "In UI::getDebrisTextures()" << endl;
    int x_off = 304;
    int y_off = 112;
    int width = 8;
    int height = 8;
    for (int i = 0; i < 4; ++i)
    {
        sf::Texture texture;
        if (i == 0)
        {
            sf::IntRect cropRect(x_off, y_off, width, height);
            texture.loadFromImage(block_sheet, cropRect);
        }
        else if (i == 1)
        {
            sf::IntRect cropRect(x_off, y_off + height, width, height);
            texture.loadFromImage(block_sheet, cropRect);
        }
        else if (i == 2)
        {
            sf::IntRect cropRect(x_off + width, y_off, width, height);
            texture.loadFromImage(block_sheet, cropRect);
        }
        else
        {
            sf::IntRect cropRect(x_off + width, y_off + height, width, height);
            texture.loadFromImage(block_sheet, cropRect);
        }
        debris1[i] = texture;
    }
}

std::vector<sf::Texture> &UI::getEnemy1()
{
    return enemy1;
}

std::vector<sf::Texture> &UI::getEnemy2()
{
    return enemy2;
}

std::vector<sf::Texture> &UI::getEnemy3()
{
    return enemy3;
}

std::vector<sf::Texture> &UI::getEnemy4()
{
    return enemy4;
}

void UI::getEnemyTextures()
{
    // cout << "In UI::getEnemyTextures()" << endl;
    int x_off = 0;
    int y_off = 16;
    int width = 16;
    int height = 16;

    // Get the normal mushroom
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 0; i < 2; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);
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
        sf::IntRect cropRect(x_off, y_off * (j + 1) + j * height, width, height);
        sf::Texture texture;
        texture.loadFromImage(enemy_sheet, cropRect);
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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
        sf::IntRect cropRect(x_off, y_off * (j + 1) + j * height, width, height);
        sf::Texture texture;
        texture.loadFromImage(enemy_sheet, cropRect);

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
        sf::IntRect cropRect(x_off, y_off * (j + 1) + j * height, width, height);
        sf::Texture texture;
        texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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
        sf::IntRect cropRect(x_off, y_off * (j + 1) + j * height, width, height);
        sf::Texture texture;
        texture.loadFromImage(enemy_sheet, cropRect);

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
        sf::IntRect cropRect(x_off, y_off * (j + 1) + j * height, width, height);
        sf::Texture texture;
        texture.loadFromImage(enemy_sheet, cropRect);

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
            sf::IntRect cropRect(x_off + i * (width), y_off * (j + 1) + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);
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
            sf::IntRect cropRect(x_off + i * (width), y_off + j * height, width, height);
            sf::Texture texture;
            texture.loadFromImage(enemy_sheet, cropRect);

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

std::vector<sf::Texture> &UI::getCoin1()
{
    return coin1;
}

std::vector<sf::Texture> &UI::getCoin2()
{
    return coin2;
}

std::vector<sf::Texture> &UI::getCoin3()
{
    return coin3;
}

std::vector<sf::Texture> &UI::getCoin4()
{
    return coin4;
}

std::vector<sf::Texture> &UI::getMushroom1()
{
    return mushroom1;
}

std::vector<sf::Texture> &UI::getMushroom2()
{
    return mushroom2;
}

std::vector<sf::Texture> &UI::getMushroom3()
{
    return mushroom3;
}

std::vector<sf::Texture> &UI::getMushroom4()
{
    return mushroom4;
}

std::vector<sf::Texture> &UI::getFlower1()
{
    return flower1;
}

std::vector<sf::Texture> &UI::getFlower2()
{
    return flower2;
}

std::vector<sf::Texture> &UI::getFlower3()
{
    return flower3;
}

std::vector<sf::Texture> &UI::getFlower4()
{
    return flower4;
}

std::vector<sf::Texture> &UI::getStar1()
{
    return star1;
}

std::vector<sf::Texture> &UI::getStar2()
{
    return star2;
}

std::vector<sf::Texture> &UI::getStar3()
{
    return star3;
}

std::vector<sf::Texture> &UI::getStar4()
{
    return star4;
}

void UI::getItemTextures()
{
    // cout << "In UI::getItemTextures()" << endl;
    int x_off = 0;
    int y_off = 0;
    int width = 16;
    int height = 16;

    // For mushrooms
    for (int j = 0; j < 4; ++j)
    {
        x_off += 9 * width * j;
        for (int i = 0; i < 4; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width), y_off, width, height);

            if (cropRect.left < 0 || cropRect.top < 0 || cropRect.left + cropRect.width > npc_sheet.getSize().x ||
                cropRect.top + cropRect.height > npc_sheet.getSize().y)
            {
                continue; // Skip if out of bounds
            }

            sf::Texture texture;
            texture.loadFromImage(npc_sheet, cropRect);
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
        x_off += 9 * width * j;
        for (int i = 0; i < 4; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width),
                                 y_off,
                                 width,
                                 height);
            if (cropRect.left < 0 || cropRect.top < 0 || cropRect.left + cropRect.width > npc_sheet.getSize().x ||
                cropRect.top + cropRect.height > npc_sheet.getSize().y)
            {
                continue;
            }

            sf::Texture texture;
            texture.loadFromImage(npc_sheet, cropRect);
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
        x_off += 9 * width * j;
        for (int i = 0; i < 4; ++i)
        {
            sf::IntRect cropRect(x_off + i * (width),
                                 y_off,
                                 width,
                                 height);
            if (cropRect.left < 0 || cropRect.top < 0 || cropRect.left + cropRect.width > npc_sheet.getSize().x ||
                cropRect.top + cropRect.height > npc_sheet.getSize().y)
            {
                continue; // Skip if out of bounds
            }
            sf::Texture texture;
            texture.loadFromImage(npc_sheet, cropRect);

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
        x_off += 9 * width * j;
        for (int i = 0; i < 4; ++i)
        {

            sf::IntRect cropRect(x_off + i * (width),
                                 y_off,
                                 width,
                                 height);
            if (cropRect.left < 0 || cropRect.top < 0 || cropRect.left + cropRect.width > npc_sheet.getSize().x ||
                cropRect.top + cropRect.height > npc_sheet.getSize().y)
            {
                continue; // Skip if out of bounds
            }
            sf::Texture texture;
            texture.loadFromImage(npc_sheet, cropRect);

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

std::vector<sf::Texture> &UI::getLuigiLarge()
{
    return luigiLarge;
}

std::vector<sf::Texture> &UI::getLuigiSmall()
{
    return luigiSmall;
}

std::vector<sf::Texture> &UI::getFireLarge()
{
    return marioLargeFire;
}
std::vector<sf::Texture> &UI::getRedLarge()
{
    return marioLargeRed;
}
std::vector<sf::Texture> &UI::getBlackLarge()
{
    return marioLargeBlack;
}

std::vector<sf::Texture> &UI::getGreenLarge()
{
    return marioLargeGreen;
}

std::vector<sf::Texture> &UI::getBlueLarge()
{
    return marioLargeBlue;
}

std::vector<sf::Texture> &UI::getFireSmall()
{
    return marioSmallFire;
}

std::vector<sf::Texture> &UI::getRedSmall()
{
    return marioSmallRed;
}

std::vector<sf::Texture> &UI::getBlackSmall()
{
    return marioSmallBlack;
}

std::vector<sf::Texture> &UI::getGreenSmall()
{
    return marioSmallGreen;
}

std::vector<sf::Texture> &UI::getBlueSmall()
{
    return marioSmallBlue;
}

void UI::loadAudio()
{
    // Load music for longer audio files
    overWorldBackGround.openFromFile("assets/Sounds/Background.mp3");
    gameOver.openFromFile("assets/Sounds/gameover.wav");

    // Load sound effects for shorter audio files
    sf::SoundBuffer levelUpBuffer;
    levelUpBuffer.loadFromFile("assets/Sounds/1up.wav");
    levelUp.setBuffer(levelUpBuffer);

    sf::SoundBuffer powerUpBuffer;
    powerUpBuffer.loadFromFile("assets/Sounds/powerup.wav");
    powerUp.setBuffer(powerUpBuffer);
}

sf::Music &UI::getOverworldBackGroundMusic()
{
    return overWorldBackGround;
}

sf::Music &UI::getGameOverMusic()
{
    return gameOver;
}

sf::Sound &UI::getLevelUpSound()
{
    return levelUp;
}

sf::Sound &UI::getPowerUpSound()
{
    return powerUp;
}

void UI::getFireBulletTextures()
{
    // cout << "In UI::getFireBulletTextures()" << endl;
    int x_off = 189;
    int y_off = 240;
    int width = 8;
    int height = 8;

    for (int i = 0; i < 4; ++i)
    {
        sf::IntRect cropRect(x_off + i * 35, y_off, width, height);
        sf::Texture texture;
        texture.loadFromImage(fire_sheet, cropRect);
        fireBullet[i] = texture;
    }

    x_off = 395;
    y_off = 236;
    width = 16;
    height = 16;
    sf::IntRect cropRect(x_off, y_off, width, height);
    sf::Texture texture;
    texture.loadFromImage(fire_sheet, cropRect);

    fireBullet[4] = texture;
}

std::vector<sf::Texture> &UI::getFireBullet()
{
    return fireBullet;
}

void UI::getBackgroundTextures()
{
    // cout << "In UI::getBackgroundTextures()" << endl;
    int x_off = 272;
    int y_off = 218;
    int width = 80;
    int height = 80;

    sf::IntRect cropRect(x_off, y_off, width, height);
    sf::Texture texture;
    texture.loadFromImage(background_sheet, cropRect);

    backgroundTextures[0] = texture;

    x_off = 48;
    y_off = 176;
    width = 48;
    height = 20;
    sf::IntRect cropRect1(x_off, y_off, width, height);
    texture.loadFromImage(background_sheet, cropRect1);
    backgroundTextures[1] = texture;

    x_off = 99;
    y_off = 160;
    width = 80;
    height = 35;
    sf::IntRect cropRect2(x_off, y_off, width, height);
    texture.loadFromImage(background_sheet, cropRect2);
    backgroundTextures[2] = texture;

    x_off = 46;
    y_off = 198;
    width = 48;
    height = 24;
    for (int i = 3; i < 6; ++i)
    {
        sf::IntRect cropRect3(x_off, y_off, width, height);
        texture.loadFromImage(background_sheet, cropRect3);
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
        sf::IntRect cropRect4(x_off, y_off, width, height);
        texture.loadFromImage(background_sheet, cropRect4);
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
    sf::IntRect cropRect5(x_off, y_off, width, height);
    texture.loadFromImage(background_sheet2, cropRect5);
    backgroundTextures[9] = texture;
}

std::vector<sf::Texture> &UI::getBackground()
{
    return backgroundTextures;
}

sf::Image &UI::getBackgroundImage()
{
    return backgroundImage;
}