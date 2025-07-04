#pragma once
#include "block.h"
#include "debris.h"
enum class NormalBlockState
{
    BeforeHit,
    AfterHit
};

class NormalBlock : public Block
{
private:
    // For animation
    NormalBlockState state;

    bool notBroken = true;

    // Timer
    int timeCount = 0;

    // For textures
    std::vector<Texture2D> textures;

    // Original position
    float originalY;

    // UI pointer
    UI *ui;

    // For debris
    Debris *debris;

public:
    NormalBlock(float x = 0, float y = 0, int scale = 0, UI *ui = nullptr);

    // For updating
    void tick();
    void render();

    // Check collision
    void playerCollision(GameObject *object);

    // For debris
    bool shouldRemoveBlock();

    // Destructor
    ~NormalBlock();
};