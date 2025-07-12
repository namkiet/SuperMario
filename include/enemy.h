#pragma once
#include "gameObject.h"
#include "UI.h"
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
    static const float GOOMBA_HEIGHT;
    static const float STOMPED_GOOMBA_HEIGHT;
    static const float KOOPA_HEIGHT;
    static const float SHELL_HEIGHT;
    static const float SHELL_WIDTH;

    // Load UI assets

    // Enemy textures
    std::vector<sf::Texture> enemyTextures;

    // Enemy properties
    float positionX;
    float positionY;
    int index = 0;
    float speed = 0.0f;
    bool isForward = false;

    EnemyCharacter enemyID;

protected:
    Handler *handler;

public:
    // Constructor
    Enemy() = default; // Default constructor
    Enemy(float x, float y, int scale, Handler *handler, UI *ui,
          sf::RenderWindow &window, EnemyCharacter id);

    // Update:
    void tick();
    void render();

    // Getting bounds
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

    // Collision check
    void collision();
    virtual void blockCollision(GameObject *object);
    virtual void pipeCollision(GameObject *object);
    virtual void playerCollision(GameObject *object);
    virtual void enemyCollision(GameObject *object);
    virtual void itemCollision(GameObject *object);

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

    float getShellHeight();
    float getKoopaHeight();
    float getShellWidth();
    float getStompedGoombaHeight();

    // Destructor
    ~Enemy();
};