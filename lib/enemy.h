#pragma once
#include "gameObject.h"
#include "UI.h"
#include "raylib.h"
#include "handler.h"
#include "animation.h"

class Handler;

enum class EnemyCharacter
{
    Goomba,      // Normal mushroom
    Koopa,       // Normal turtle
    KoopaTroopa, // Flying turtle
    CheepCheep   // Fish
};

class Enemy : public GameObject
{
private:
    // Constant values
    static const float WIDTH;
    static const float HEIGHT;

    // Load UI assets

    // Enemy textures
    std::vector<Texture2D> enemyTextures;

    // Enemy properties
    float positionX;
    float positionY;
    int index = 0;
    float speed = 0.0f;
    bool isForward = false;

    EnemyCharacter enemyID;

protected:
    UI *ui;
    Handler *handler;

public:
    // Constructor
    Enemy(float x = 0, float y = 0, int index = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr, EnemyCharacter id = EnemyCharacter::Goomba);

    // Update:
    void tick();
    void render();

    // Getting bounds
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();

    // Collision check
    void collision();
    virtual void blockCollision(GameObject *object);
    virtual void pipeCollision(GameObject *object);
    virtual void playerCollision(GameObject *object);
    virtual void enemyCollision(GameObject *object);

    // Getters and setters
    void setEnemyID(EnemyCharacter id);
    EnemyCharacter getEnemyID();

    // Check if the enemy should be removed
    virtual bool shouldRemove();

    // Check if the enemy is dead or not
    virtual bool isDead();

    // Check if the enemy is stomped on or not
    bool isStomped();

    //
    virtual bool isShell();

    // Destructor
    ~Enemy();
};