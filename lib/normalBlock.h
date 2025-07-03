#pragma once
#include "block.h"

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
    int timeCount =0;

    std::vector<Texture2D> textures;

    float originalY;

public:
    NormalBlock(float x = 0, float y = 0, int scale = 0, UI *ui = nullptr);

    // For updating
    void tick();
    void render();

    // Check collision
    void playerCollision(GameObject *object);
};