#pragma once
#include "item.h"
#include "handler.h"

enum class StarState
{
    Normal,
    Collected
};

class Star : public Item
{
private:
    // For animation
    Animation currentAnimation;

    // For textures
    std::vector<Texture2D> textures;

    // State
    StarState state;

    // Timer
    int timeCount = 0;

    //
    bool isCollected = false;

    // Handler pointer
    Handler *handler;

    // UI pointer
    UI *ui;

    // Original Y position for gravity effect
    float originalY = 0;

    // First time flag for gravity effect
    bool firstTime = true;

public:
    Star(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    // Check collision
    void collision();
    void playerCollision();
    void pipeCollision(GameObject *object);
    void blockCollision(GameObject *object);
};