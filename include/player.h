#pragma once
#include <vector>
#include "gameObject.h"
#include "handler.h"
#include "UI.h"
#include "animation.h"

class Handler;
class Fire;

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
    RandomBeforeStar,
    Star,
    Dead,
    Win
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

    // State, type, and ID
    PlayerState state;
    PlayerType type;
    PlayerID id;
    PlayerType previousType; // For storing previous type

    // For animation
    Animation *normalMarioWalkL = nullptr;
    Animation *normalMarioWalkS = nullptr;
    Animation *normalLuigiWalkL = nullptr;
    Animation *normalLuigiWalkS = nullptr;
    Animation *fireWalkL = nullptr;
    Animation *redWalkL = nullptr;
    Animation *blackWalkL = nullptr;
    Animation *greenWalkL = nullptr;
    Animation *blueWalkL = nullptr;
    Animation *currentAnimation = nullptr;

    // Player textures
    std::vector<sf::Texture> normalMarioLargeTextures;
    std::vector<sf::Texture> normalMarioSmallTextures;
    std::vector<sf::Texture> normalLuigiLargeTextures;
    std::vector<sf::Texture> normalLuigiSmallTextures;
    std::vector<sf::Texture> fireLargeTextures;
    std::vector<sf::Texture> fireSmallTextures;
    std::vector<sf::Texture> currentPlayerTextures;

    // Random textures when eating stars or flowers
    std::vector<sf::Texture> randomTextures1; // Idle -> 0
    std::vector<sf::Texture> randomTextures2; // Walk1 -> 1
    std::vector<sf::Texture> randomTextures3; // Walk2 -> 2
    std::vector<sf::Texture> randomTextures4; // Walk3 -> 3
    std::vector<sf::Texture> randomTextures5; // Walk4 -> 4
    std::vector<sf::Texture> randomTextures6; // Jumping -> 5

    // Textures for star type
    std::vector<sf::Texture> starModeLargeTexturesWalk; // Random textures for star mode
    std::vector<sf::Texture> starModeSmallTexturesWalk; // Random textures for star mode
    std::vector<sf::Texture> starModeLargeTexturesJump; // Jumping textures for star mode
    std::vector<sf::Texture> starModeSmallTexturesJump; // Jumping textures for star mode
    std::vector<sf::Texture> starModeLargeTextures;     // Textures for large star mode
    std::vector<sf::Texture> starModeSmallTextures;     // Textures for small

    // Textures for win state
    std::vector<sf::Texture> winLargeTextures; // Textures for win state
    std::vector<sf::Texture> winSmallTextures; // Textures for win state

    // Load textures from UI
    void LoadPlayerTextures();
    void LoadRandomTextures();

    // Idle and dead texture:
    sf::Texture idleTexture;
    sf::Texture deadTexture;
    sf::Texture jumpTexture;

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
    void backgroundCollision(GameObject *object);

    // For player texture animation
    int index = 0; // Index for player texture animation

    // For removed blocks
    std::vector<GameObject *> removedBlocks;
    std::vector<GameObject *> removedEnemies;
    std::vector<GameObject *> removedItems;

    // For time count
    int timeCountForDeath = 0;
    int timeCountForRandomTextures = 0;
    int timeCountForGrowingUp = 0;
    int timeCountForFire = 0;
    int timeCountForStar = 0;

    //
    bool finishedCollisionChecking = false;

    //
    void setState(PlayerState newState);
    void setType(PlayerType newType);
    void setPlayerID(PlayerID newID);

    // Original scale
    int originalScale = 0;
    float originalHeight = 0.0f;

    // For fire mario
    Fire *fireBullet = nullptr;

    // For locking the mario for a while when growing up and random
    bool isLocked = false;

public:
    // Constructor
    Player() = default;
    Player(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window,
           PlayerID id, PlayerType type, PlayerState state);

    // For updating
    void tick();
    void render();

    // For checking collision
    sf::FloatRect getBounds();      // Get the lower half bounds of the object
    sf::FloatRect getBoundsTop();   // Get the upper half bounds of the object
    sf::FloatRect getBoundsRight(); // Get the right half bounds of the object
    sf::FloatRect getBoundsLeft();  // Get the left half bounds of the object

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

    // For fire mario
    void fire();
    bool isFireMario();

    // Checking if the player is locked
    bool isPlayerLocked();

    // Check the direction of the player
    bool isPlayerForward();

    // Destructor
    ~Player();
};