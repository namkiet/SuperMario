#pragma once
#include "item.h"
#include "handler.h"

enum class MushroomState
{
    Normal,   // Normal state
    Collected // Collected state
};

class Mushroom : public Item
{
private:
    // For animation
    std::vector<Texture2D> textures;

    // Timer
    int timeCount = 0;

    //
    bool isCollected = false;

    // speed
    float speed = -2.0f;

    // state
    MushroomState state;

    // Handler pointer
    Handler *handler;

    // UI pointer
    UI *ui;

    //
    float originalY = 0; // Original Y position for gravity effect
    bool firstTime = true;

public:
    Mushroom(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    // Check collision
    void collision();
    void playerCollision();
    void pipeCollision(GameObject *object);
    void blockCollision(GameObject *object);
};