#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class UI
{
private:
    // Constant values
    static const int MARIO_L_COUNT = 21;
    static const int MARIO_S_COUNT = 14;
    static const int TILE_1_COUNT = 28;
    static const int TILE_2_COUNT = 33;
    static const int ENEMY_COUNT = 31;

    // Images and textures
    sf::Image player_sheet; // Character spritesheet
    sf::Image enemy_sheet;  // Enemy spritesheet
    sf::Image npc_sheet;    // NPC and items spritesheet
    sf::Image block_sheet;  // Block spritesheet
    sf::Image tile_sheet;   // Tile and pipes spritesheet
    sf::Image fire_sheet;   // For mario fire mode
    sf::Image game_over_sheet;
    sf::Image intro_sheet;
    sf::Image background_sheet; // Background spritesheet
    sf::Image background_sheet2;

    // Textures for the player
    std::vector<sf::Texture> marioLarge{MARIO_L_COUNT};
    std::vector<sf::Texture> luigiLarge{MARIO_L_COUNT};

    std::vector<sf::Texture> marioSmall{MARIO_S_COUNT};
    std::vector<sf::Texture> luigiSmall{MARIO_S_COUNT};

    std::vector<sf::Texture> marioLargeFire{MARIO_L_COUNT};
    std::vector<sf::Texture> marioSmallFire{MARIO_S_COUNT};

    std::vector<sf::Texture> marioLargeRed{MARIO_L_COUNT};
    std::vector<sf::Texture> marioSmallRed{MARIO_S_COUNT};

    std::vector<sf::Texture> marioLargeBlack{MARIO_L_COUNT};
    std::vector<sf::Texture> marioSmallBlack{MARIO_S_COUNT};

    std::vector<sf::Texture> marioLargeGreen{MARIO_L_COUNT};
    std::vector<sf::Texture> marioSmallGreen{MARIO_S_COUNT};

    std::vector<sf::Texture> marioLargeBlue{MARIO_L_COUNT};
    std::vector<sf::Texture> marioSmallBlue{MARIO_S_COUNT};

    // Textures for tiles and blocks
    std::vector<sf::Texture> tile1{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<sf::Texture> tile2{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<sf::Texture> tile3{TILE_1_COUNT + TILE_2_COUNT};
    std::vector<sf::Texture> tile4{TILE_1_COUNT + TILE_2_COUNT};

    // Textures for pipes
    std::vector<sf::Texture> pipe1{4};

    // Texture for debris
    std::vector<sf::Texture> debris1{4};

    // Textures for enemies
    std::vector<sf::Texture> enemy1{ENEMY_COUNT};
    std::vector<sf::Texture> enemy2{ENEMY_COUNT};
    std::vector<sf::Texture> enemy3{ENEMY_COUNT};
    std::vector<sf::Texture> enemy4{ENEMY_COUNT};

    // Textures for coins
    std::vector<sf::Texture> coin1{4};
    std::vector<sf::Texture> coin2{4};
    std::vector<sf::Texture> coin3{4};
    std::vector<sf::Texture> coin4{4};

    // Textures for items
    std::vector<sf::Texture> mushroom1{4};
    std::vector<sf::Texture> mushroom2{4};
    std::vector<sf::Texture> mushroom3{4};
    std::vector<sf::Texture> mushroom4{4};
    std::vector<sf::Texture> flower1{4};
    std::vector<sf::Texture> flower2{4};
    std::vector<sf::Texture> flower3{4};
    std::vector<sf::Texture> flower4{4};
    std::vector<sf::Texture> star1{4};
    std::vector<sf::Texture> star2{4};
    std::vector<sf::Texture> star3{4};
    std::vector<sf::Texture> star4{4};

    // Textures for fire mode
    std::vector<sf::Texture> fireBullet{5}; // 4 normal + 1 boomed

    // Textures for background
    std::vector<sf::Texture> backgroundTextures{10};

    // Load textures from images
    void getLargePlayerTextures();
    void getSmallPlayerTextures();
    void getTileTextures();
    void getPipeTextures();
    void getDebrisTextures();
    void getEnemyTextures();
    void getItemTextures();
    void getFireBulletTextures();
    void getBackgroundTextures();

    // For levelHandler.cpp
    sf::Image levelImage;
    sf::Image characterImage;
    sf::Image backgroundImage;

    // Music for the game
    sf::Music overWorldBackGround;
    sf::Music gameOver;

    // Sound effects
    sf::Sound coin;
    sf::Sound death;

    sf::Sound levelUp;
    sf::Sound powerUp;

public:
    // Constructor
    UI();

    // Destructor
    ~UI();

    // Getter methods
    std::vector<sf::Texture> &getMarioLarge();
    std::vector<sf::Texture> &getMarioSmall();
    std::vector<sf::Texture> &getTile1();
    std::vector<sf::Texture> &getTile2();
    std::vector<sf::Texture> &getTile3();
    std::vector<sf::Texture> &getTile4();
    std::vector<sf::Texture> &getPipe1();
    std::vector<sf::Texture> &getDebris1();
    std::vector<sf::Texture> &getEnemy1();
    std::vector<sf::Texture> &getEnemy2();
    std::vector<sf::Texture> &getEnemy3();
    std::vector<sf::Texture> &getEnemy4();
    std::vector<sf::Texture> &getCoin1();
    std::vector<sf::Texture> &getCoin2();
    std::vector<sf::Texture> &getCoin3();
    std::vector<sf::Texture> &getCoin4();
    std::vector<sf::Texture> &getMushroom1();
    std::vector<sf::Texture> &getMushroom2();
    std::vector<sf::Texture> &getMushroom3();
    std::vector<sf::Texture> &getMushroom4();
    std::vector<sf::Texture> &getFlower1();
    std::vector<sf::Texture> &getFlower2();
    std::vector<sf::Texture> &getFlower3();
    std::vector<sf::Texture> &getFlower4();
    std::vector<sf::Texture> &getStar1();
    std::vector<sf::Texture> &getStar2();
    std::vector<sf::Texture> &getStar3();
    std::vector<sf::Texture> &getStar4();
    std::vector<sf::Texture> &getLuigiLarge();
    std::vector<sf::Texture> &getLuigiSmall();
    std::vector<sf::Texture> &getFireLarge();
    std::vector<sf::Texture> &getFireSmall();
    std::vector<sf::Texture> &getRedLarge();
    std::vector<sf::Texture> &getRedSmall();
    std::vector<sf::Texture> &getBlackLarge();
    std::vector<sf::Texture> &getBlackSmall();
    std::vector<sf::Texture> &getGreenLarge();
    std::vector<sf::Texture> &getGreenSmall();
    std::vector<sf::Texture> &getBlueLarge();
    std::vector<sf::Texture> &getBlueSmall();
    std::vector<sf::Texture> &getFireBullet();
    std::vector<sf::Texture> &getBackground();

    sf::Music &getOverworldBackGroundMusic();
    sf::Music &getGameOverMusic();

    sf::Sound &getLevelUpSound();
    sf::Sound &getPowerUpSound();

    sf::Image &getLevelImage();
    sf::Image &getCharacterImage();
    sf::Image &getBackgroundImage();

    // Load and unload images
    void loadImages();
    void loadAudio();
};
