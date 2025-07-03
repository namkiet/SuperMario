#pragma once
#include <vector>
#include <raylib.h>
#include "gameObject.h"
#include "handler.h"
#include "UI.h"
#include "animation.h"
class Handler;

enum class PlayerState
{
    Small,
    Large
};

class Player : public GameObject
{
private:
    static const float WIDTH;
    static const float HEIGHT;

    Handler *handler;
    UI *ui;
    PlayerState state;
    Animation playerWalkL, playerWalkS;
    Animation currentAnimation;

    // Player textures
    std::vector<Texture2D> playerTexturesLarge;
    std::vector<Texture2D> playerTexturesSmall;
    std::vector<Texture2D> smallTemp;
    std::vector<Texture2D> largeTemp;
    std::vector<Texture2D> currentPlayerTextures;

    //
    void showBounds();
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

    // For player texture animation
    int index = 0; // Index for player texture animation

    // For removed blocks
    std::vector<GameObject *> removedBlocks;
    std::vector<GameObject *> removedEnemies;

    // For time count
    int timeCount = 0;

    // 
    bool finishedCollisionChecking = false;

public:
    Player(float x, float y, int index, int scale, Handler *handler, UI *ui);

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

    // For checking if the player is dead
    bool isDead();

    // For checking if the player is playing death animation
    bool isStomped(); // I know it weird but just use to synchronize with the gameObject class

    // For checking if the player is already check for collision
    bool playerFinishedCollisionChecking();
    void setPlayerFinishedCollisionChecking(bool finished);
    
    // For getting small or large mario
    bool isSmallMario();
    
    // Destructor
    ~Player() = default; // Default destructor
};