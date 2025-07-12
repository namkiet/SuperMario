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
    std::vector<sf::Texture> textures;

    // Timer
    int timeCount = 0;

    // Original Y position for gravity effect
    float originalY = 0;

    // Handler pointer
    Handler *handler;

public:
    LevelUpBlock() = default; // Default constructor
    LevelUpBlock(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    // Player collision
    void playerCollision(GameObject *object);

    GameObject *getMushroom();
    void setMushroom();
};