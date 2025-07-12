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
    Animation *normalKoopa = nullptr;

    // For shell animation
    Animation *shellKoopa = nullptr;

    // For current animation
    Animation *currentAnimation = nullptr;
    KoopaState state;

    // For textures
    std::vector<sf::Texture> koopaTextures;

    // For position and speed

    int timeCountForDeath = 0;       // If this one run out, the koopa will be removed
    int timeCountForShell = 0;       // Timer for shell state
    int timeCountForShellMoving = 0; // Timer for shell moving state

    bool isForward = false;

public:
    Koopa() = default;
    Koopa(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window);

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
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

    //
    bool isShell();

    // Set state of koopa from player
    void setState(KoopaState newState);

    KoopaState getState();

    // Destructor
    ~Koopa();
};