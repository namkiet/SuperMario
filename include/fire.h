#pragma once
#include "item.h"

class Handler;

enum class FireState
{
    Normal,
    Boomed
};

class Fire : public Item
{
private:
    // For animation
    Animation* currentAnimation = nullptr;

    // Fire textures
    std::vector<sf::Texture> fireTextures;

    // Handler pointer
    Handler *handler;

    // State
    FireState state;

    bool isBoomed = false;

    int timeCountForBoomed = 0; // For the time count of boomed state
    int timeCountForNormal = 0;

    bool renderBoomedFinished = false;
    bool renderNormalFinished = false;

public:
    // Constructor
    Fire() = default; // Default constructor
    Fire(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window);
    // Update:
    void tick();
    void render();

    void collision();
    void enemyCollision();
    void blockCollision(GameObject *object);
    void pipeCollision(GameObject *object);

    bool shouldRemoveItem();
    bool isStomped();

    // Maximum number of fire bullets
    static int count;
    ~Fire();
};