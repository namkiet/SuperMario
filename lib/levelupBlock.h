#pragma once
#include "block.h"
#include "mushroom.h"
#include "UI.h"
#include "handler.h"

enum class LevelUpBlockState
{
    BeforeHit,
    AfterHit
};

class LevelUpBlock : public Block
{
private:
    // State
    LevelUpBlockState state;

    // Mushroom animation
    Mushroom *mushroom;

    // For textures
    std::vector<Texture2D> textures;

    // UI pointer
    UI *ui;

    // Timer
    int timeCount = 0;

    // Original Y position for gravity effect
    float originalY = 0;

    // Handler pointer
    Handler *handler;

public:
    LevelUpBlock(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    // Player collision
    void playerCollision(GameObject *object);

    GameObject *getMushroom();
    void setMushroom();
};