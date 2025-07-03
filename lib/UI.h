#pragma once
#include <raylib.h>
#include <vector>
// #define RES_PATH "C:\\Minh Tam\\CS202_Project\\res\\"

class UI
{
private:
    // Constant values
    static const int MARIO_L_COUNT = 21;
    static const int MARIO_S_COUNT = 14;
    static const int TILE_1_COUNT = 28;
    static const int TILE_2_COUNT = 33;
    static const int ENEMY_COUNT = 44;
    // Images and textures
    Image player_sheet; // Character spritesheet
    Image enemy_sheet;  // Enemy spritesheet
    Image npc_sheet;    // NPC spritesheet
    Image block_sheet;  // Block spritesheet
    Image tile_sheet;   // Tile and pipes spritesheet
    Image game_over_sheet;
    Image intro_sheet;

    // Textures for the game
    std::vector<Texture2D> marioLarge{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmall{MARIO_S_COUNT};
    std::vector<Texture2D> tile1{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile2{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile3{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile4{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> pipe1{4};
    std::vector<Texture2D> debris1{4};
    std::vector<Texture2D> enemy1{ENEMY_COUNT};
    std::vector<Texture2D> enemy2{ENEMY_COUNT};
    std::vector<Texture2D> enemy3{ENEMY_COUNT};
    std::vector<Texture2D> enemy4{ENEMY_COUNT};

    // Load textures from images
    void getPlayerTextures();
    void getTileTextures();
    void getPipeTextures();
    void getDebrisTextures();
    void getEnemyTextures();

    // For levelHandler.cpp
    Image levelImage;
    Image characterImage;

public:
    // Constructor
    UI();

    // Destructor
    ~UI();

    // Getter methods
    std::vector<Texture2D> &getMarioLarge();
    std::vector<Texture2D> &getMarioSmall();
    std::vector<Texture2D> &getTile1();
    std::vector<Texture2D> &getTile2();
    std::vector<Texture2D> &getTile3();
    std::vector<Texture2D> &getTile4();
    std::vector<Texture2D> &getPipe1();
    std::vector<Texture2D> &getDebris1();
    std::vector<Texture2D> &getEnemy1();
    std::vector<Texture2D> &getEnemy2();
    std::vector<Texture2D> &getEnemy3();
    std::vector<Texture2D> &getEnemy4();

    Image &getLevelImage();
    Image &getCharacterImage();

    // Load and unload images
    void loadImages();
    void unloadImages();
};
