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
    std::vector<sf::Texture> textures;

    // Timer
    int timeCount = 0;

    float originalY; // Store the original Y position of the block

    // Handler pointer
    Handler *handler;

public:
    StarBlock() = default; // Default constructor
    StarBlock(float x, float y, int scale, Handler *handler,
              UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    void playerCollision(GameObject *object);

    GameObject *getStar();
    void setStar();
};