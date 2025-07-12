#pragma once
#include <vector>
#include "enemy.h"

enum class GoombaState
{
    Normal,
    Stomped,
    Dead,        // by player
    DeadByEnemy, // by other enemies such as shell
    DeadByFire   // by fire bullet
};

class Goomba : public Enemy
{
private:
    // For animation
    Animation *normalGoomba;
    Animation *currentAnimation;
    GoombaState state;

    // For textures
    std::vector<sf::Texture> goombaTextures;

    // For position and speed
    int timeCount = 0;

    //
    // bool isPlayingDeath = false;

    void setState(GoombaState newState);

public:
    // Constructor
    Goomba()=default;
    Goomba(float x, float y, int scale, Handler *handler,
           UI *ui, sf::RenderWindow &window);

    // Update:
    void render();
    void tick();

    // Check collision
    void collision();
    void blockCollision(GameObject *object);
    void pipeCollision(GameObject *object);
    void playerCollision(GameObject *object);
    void enemyCollision(GameObject *object);
    void itemCollision(GameObject *object);

    // Check if the Goomba should be removed
    bool shouldRemove();

    // Check if the Goomba is dead
    bool isDead();

    // Check if the Goomba is stomped on or not
    bool isStomped();

    // Check bounds
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

    // Destructor
    ~Goomba();
};