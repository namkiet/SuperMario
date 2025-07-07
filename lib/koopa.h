#pragma once
#include <vector>
#include "enemy.h"
enum class KoopaState
{
    Normal,
    Flying,
    Shell,       // In shell state, not moving
    ShellMoving, // In shell state, not moving, but have legs
    DeadByFire,
    Dead
};

class Koopa : public Enemy
{
private:
    // For normal animation
    Animation normalKoopa;

    // For shell animation
    Animation shellKoopa;

    // For current animation
    Animation currentAnimation;
    KoopaState state;

    // For textures
    std::vector<Texture2D> koopaTextures;

    // For position and speed

    int timeCountForDeath = 0;       // If this one run out, the koopa will be removed
    int timeCountForShell = 0;       // Timer for shell state
    int timeCountForShellMoving = 0; // Timer for shell moving state

    bool isForward = false;

public:
    Koopa(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update:
    void render();
    void tick();

    // Check collision
    void collision();
    void blockCollision(GameObject *object);
    void pipeCollision(GameObject *object);
    void playerCollision(int mode);
    void enemyCollision(GameObject *object);
    void itemCollision(GameObject *object);

    // Check if the Koopa should be removed
    bool shouldRemove();

    // Check if the Koopa is dead
    bool isDead();

    // Check if the Koopa is stomped on or not
    bool isStomped();
    void setStomped(bool newState);

    // Check bounds for koopa
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();

    //
    bool isShell();

    // Set state of koopa from player
    void setState(KoopaState newState);

    KoopaState getState();
};