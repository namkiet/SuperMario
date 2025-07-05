#pragma once
#include <raylib.h>
#include <vector>
#include <stdio.h>
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
    Image npc_sheet;    // NPC and items spritesheet
    Image block_sheet;  // Block spritesheet
    Image tile_sheet;   // Tile and pipes spritesheet
    Image fire_sheet;   // For mario fire mode
    Image game_over_sheet;
    Image intro_sheet;

    // Textures for the player
    std::vector<Texture2D> marioLarge{MARIO_L_COUNT};
    std::vector<Texture2D> luigiLarge{MARIO_L_COUNT};

    std::vector<Texture2D> marioSmall{MARIO_S_COUNT};
    std::vector<Texture2D> luigiSmall{MARIO_S_COUNT};

    std::vector<Texture2D> marioLargeFire{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmallFire{MARIO_S_COUNT};

    std::vector<Texture2D> marioLargeRed{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmallRed{MARIO_S_COUNT};

    std::vector<Texture2D> marioLargeBlack{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmallBlack{MARIO_S_COUNT};

    std::vector<Texture2D> marioLargeGreen{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmallGreen{MARIO_S_COUNT};

    std::vector<Texture2D> marioLargeBlue{MARIO_L_COUNT};
    std::vector<Texture2D> marioSmallBlue{MARIO_S_COUNT};

    // Textures for tiles and blocks
    std::vector<Texture2D> tile1{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile2{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile3{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<Texture2D> tile4{TILE_1_COUNT + TILE_2_COUNT};

    // Textures for pipes
    std::vector<Texture2D> pipe1{4};

    // Texture for debris
    std::vector<Texture2D> debris1{4};

    // Textures for enemies
    std::vector<Texture2D> enemy1{ENEMY_COUNT};
    std::vector<Texture2D> enemy2{ENEMY_COUNT};
    std::vector<Texture2D> enemy3{ENEMY_COUNT};
    std::vector<Texture2D> enemy4{ENEMY_COUNT};

    // Textures for coins
    std::vector<Texture2D> coin1{4};
    std::vector<Texture2D> coin2{4};
    std::vector<Texture2D> coin3{4};
    std::vector<Texture2D> coin4{4};

    // Textures for items
    std::vector<Texture2D> mushroom1{4};
    std::vector<Texture2D> mushroom2{4};
    std::vector<Texture2D> mushroom3{4};
    std::vector<Texture2D> mushroom4{4};
    std::vector<Texture2D> flower1{4};
    std::vector<Texture2D> flower2{4};
    std::vector<Texture2D> flower3{4};
    std::vector<Texture2D> flower4{4};
    std::vector<Texture2D> star1{4};
    std::vector<Texture2D> star2{4};
    std::vector<Texture2D> star3{4};
    std::vector<Texture2D> star4{4};

    // Textures for fire mode
    std::vector<Texture2D> fireBullet{4};

    // Load textures from images
    void getLargePlayerTextures();
    void getSmallPlayerTextures();
    void getTileTextures();
    void getPipeTextures();
    void getDebrisTextures();
    void getEnemyTextures();
    void getItemTextures();
    void getFireBulletTextures();

    // For levelHandler.cpp
    Image levelImage;
    Image characterImage;

    // Music for the game
    Music overWorldBackGround;
    Music gameOver;

    // Sound effects
    Sound coin;
    Sound death;

    Sound levelUp;
    Sound powerUp;

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
    std::vector<Texture2D> &getCoin1();
    std::vector<Texture2D> &getCoin2();
    std::vector<Texture2D> &getCoin3();
    std::vector<Texture2D> &getCoin4();
    std::vector<Texture2D> &getMushroom1();
    std::vector<Texture2D> &getMushroom2();
    std::vector<Texture2D> &getMushroom3();
    std::vector<Texture2D> &getMushroom4();
    std::vector<Texture2D> &getFlower1();
    std::vector<Texture2D> &getFlower2();
    std::vector<Texture2D> &getFlower3();
    std::vector<Texture2D> &getFlower4();
    std::vector<Texture2D> &getStar1();
    std::vector<Texture2D> &getStar2();
    std::vector<Texture2D> &getStar3();
    std::vector<Texture2D> &getStar4();
    std::vector<Texture2D> &getLuigiLarge();
    std::vector<Texture2D> &getLuigiSmall();
    std::vector<Texture2D> &getFireLarge();
    std::vector<Texture2D> &getFireSmall();
    std::vector<Texture2D> &getRedLarge();
    std::vector<Texture2D> &getRedSmall();
    std::vector<Texture2D> &getBlackLarge();
    std::vector<Texture2D> &getBlackSmall();
    std::vector<Texture2D> &getGreenLarge();
    std::vector<Texture2D> &getGreenSmall();
    std::vector<Texture2D> &getBlueLarge();
    std::vector<Texture2D> &getBlueSmall();
    std::vector<Texture2D> &getFireBullet();
    
    Music &getOverworldBackGroundMusic();
    Music &getGameOverMusic();

    Sound &getLevelUpSound();
    Sound &getPowerUpSound();

    Image &getLevelImage();
    Image &getCharacterImage();

    // Load and unload images
    void loadImages();
    void loadAudio();
    void unloadImages();
    void unloadAudio();
};
