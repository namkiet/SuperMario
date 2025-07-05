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
    Animation currentAnimation;

    // Fire textures
    std::vector<Texture2D> fireTextures;

    // UI pointer
    UI *ui;

    // Handler pointer
    Handler *handler;

    // State
    FireState state;

    bool isBoomed = false;

    int timeCountForBoomed = 0; // For the time count of boomed state

public:
    // Constructor
    Fire(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update:
    void tick();
    void render();

    void collision();
    void enemyCollision();
    void blockCollision(GameObject *object);

    bool shouldRemoveItem();
    bool isStomped();
    // Maximum number of fire bullets
    static int count;
    ~Fire();
};