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
    std::vector<sf::Texture> textures;

    // Original position
    float originalY;

    // For debris
    Debris *debris;

public:
    NormalBlock() = default; // Default constructor
    NormalBlock(float x, float y, int scale, UI *ui, sf::RenderWindow &window);

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