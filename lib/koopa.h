#pragma once
#include <vector>
#include "enemy.h"
enum class KoopaState
{
    Normal,
    Flying,
    Stomped,
    Shell, // Normal turle but in shell
    ShellMoving,
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
    int timeCount = 0; // For stomp
    int mode = 0;      // 0: Not continue to stomp, 1: Continue to stomp

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
    void playerCollision(GameObject *object);
    void enemyCollision(GameObject *object);

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
};