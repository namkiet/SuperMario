#pragma once
#include <vector>
#include "enemy.h"

enum class GoombaState
{
    Normal,
    Stomped,
    Dead,       // by player
    DeadByEnemy // by other enemies such as shell and bullet
};

class Goomba : public Enemy
{
private:
    // For animation
    Animation normalGoomba;
    Animation currentAnimation;
    GoombaState state;

    // For textures
    std::vector<Texture2D> goombaTextures;

    // For position and speed
    int timeCount = 0;

    //
    // bool isPlayingDeath = false;

public:
    // Constructor
    Goomba(float x = 0, float y = 0, int index = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update:
    void render();
    void tick();

    // Check collision
    void collision();
    void blockCollision(GameObject *object);
    void pipeCollision(GameObject *object);
    void playerCollision(GameObject *object);
    void enemyCollision(GameObject *object);

    // Check if the Goomba should be removed
    bool shouldRemove();

    // Check if the Goomba is dead
    bool isDead();

    // Check if the Goomba is stomped on or not
    bool isStomped();

    // Check bounds for Goomba
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();
};