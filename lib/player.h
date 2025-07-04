#pragma once
#include <vector>
#include <raylib.h>
#include "gameObject.h"
#include "handler.h"
#include "UI.h"
#include "animation.h"
class Handler;

enum class PlayerID
{
    Mario,
    Luigi
};

enum class PlayerType
{
    Normal,
    RandomBeforeFire,
    Fire,
    Star
};

enum class PlayerState
{
    Small,
    GrowingUp,
    Large
};

enum class PlayerActivity
{
    Walk,
    Swim
};

class Player : public GameObject
{
private:
    // Constant values
    static const float WIDTH;
    static const float HEIGHT;

    // Handler pointer
    Handler *handler;

    // UI pointer
    UI *ui;

    // State, type, and ID
    PlayerState state;
    PlayerType type;
    PlayerID id;
    PlayerType previousType; // For storing previous type

    // For animation
    Animation normalMarioWalkL, normalMarioWalkS;
    Animation normalLuigiWalkL, normalLuigiWalkS;
    Animation fireWalkL;
    Animation redWalkL;
    Animation blackWalkL;
    Animation greenWalkL;
    Animation blueWalkL;
    Animation currentAnimation;

    // Player textures
    std::vector<Texture2D> normalMarioLargeTextures;
    std::vector<Texture2D> normalMarioSmallTextures;
    std::vector<Texture2D> normalLuigiLargeTextures;
    std::vector<Texture2D> normalLuigiSmallTextures;
    std::vector<Texture2D> fireLargeTextures;
    std::vector<Texture2D> fireSmallTextures;
    std::vector<Texture2D> currentPlayerTextures;

    // Random textures when eating stars or flowers
    std::vector<Texture2D> randomTextures1; // Idle -> 0
    std::vector<Texture2D> randomTextures2; // Walk1 -> 1
    std::vector<Texture2D> randomTextures3; // Walk2 -> 2
    std::vector<Texture2D> randomTextures4; // Walk3 -> 3
    std::vector<Texture2D> randomTextures5; // Walk4 -> 4
    std::vector<Texture2D> randomTextures6; // Jumping -> 5

    // Textures for star type
    std::vector<Texture2D> starModeLargeTexturesWalk; // Random textures for star mode
    std::vector<Texture2D> starModeSmallTexturesWalk; // Random textures for star mode
    std::vector<Texture2D> starModeLargeTexturesJump; // Jumping textures for star mode
    std::vector<Texture2D> starModeSmallTexturesJump; // Jumping textures for star mode
    std::vector<Texture2D> starModeLargeTextures;     // Textures for large star mode
    std::vector<Texture2D> starModeSmallTextures;     // Textures for small

    // Load textures from UI
    void LoadPlayerTextures();
    void LoadRandomTextures();

    // Idle and dead texture:
    Texture2D idleTexture;
    Texture2D deadTexture;
    Texture2D jumpTexture;

    bool isPlayingDeath = false;

    // For jumping
    bool jumped = false;

    // For direction
    bool forward = false;

    // For collision detection
    void collision();
    void blockCollision(GameObject *object);
    void pipeCollision(GameObject *object);
    void enemyCollision(GameObject *object);
    void itemCollision(GameObject *object);

    // For player texture animation
    int index = 0; // Index for player texture animation

    // For removed blocks
    std::vector<GameObject *> removedBlocks;
    std::vector<GameObject *> removedEnemies;
    std::vector<GameObject *> removeItems;

    // For time count
    int timeCountForDeath = 0;
    int timeCountForRandomTextures = 0;
    int timeCountForGrowingUp = 0;

    //
    bool finishedCollisionChecking = false;

    //
    void setState(PlayerState newState);
    void setType(PlayerType newType);
    void setPlayerID(PlayerID newID);

    // Original scale
    int originalScale = 0;
    float originalHeight = 0.0f;

public:
    // Constructor
    Player(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr,
           PlayerID id = PlayerID::Mario, PlayerType type = PlayerType::Normal, PlayerState state = PlayerState::Small);

    // For updating
    void tick();
    void render();

    // For checking collision
    Rectangle getBounds();      // Get the lower half bounds of the object
    Rectangle getBoundsTop();   // Get the upper half bounds of the object
    Rectangle getBoundsRight(); // Get the right half bounds of the object
    Rectangle getBoundsLeft();  // Get the left half bounds of the object

    // For jump handling
    bool hasJumped();
    void setJump(bool jump);

    // For handler class
    std::vector<GameObject *> getAndResetRemovedBlocks();
    std::vector<GameObject *> getAndResetRemovedEnemies();
    std::vector<GameObject *> getAndResetRemovedItems();

    // For checking if the player is dead
    bool isDead();

    // For checking if the player is playing death animation
    bool isStomped(); // I know it weird but just use to synchronize with the gameObject class

    // For checking if the player is already check for collision
    bool playerFinishedCollisionChecking();
    void setPlayerFinishedCollisionChecking(bool finished);

    // For getting small or large mario
    bool isSmallMario();

    // Set random
    void setRandomTextures(int index);

    // Destructor
    ~Player() = default; // Default destructor
};