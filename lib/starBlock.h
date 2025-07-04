#pragma once
#include "block.h"
#include "star.h"

enum class StarBlockState
{
    BeforeHit,
    AfterHit
};
class StarBlock : public Block
{
private:
    // For animation
    StarBlockState state;

    // Star animation
    Star *star;

    // For textures
    std::vector<Texture2D> textures;

    // UI pointer
    UI *ui;

    // Timer
    int timeCount = 0;

    float originalY; // Store the original Y position of the block

    // Handler pointer
    Handler *handler;

public:
    StarBlock(float x = 0, float y = 0, int scale = 0, Handler *handler = nullptr, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    void playerCollision(GameObject *object);
};