#pragma once
#include <raylib.h>
#include <vector>
#include "gameObject.h"
#include "UI.h"
#include "debris.h"
#include "animation.h"

enum class BlockType
{
    Normal,
    Question,
    Coin,
    Stairs,
    Ground,
    LevelUp,
    Star,
    Flag
};

class Block : public GameObject
{
private:
    // Load UI assets
    static const float WIDTH;
    static const float HEIGHT;

    // UI pointer
    UI *ui;

    // Block textures
    std::vector<Texture2D> blockTextures;

    int index = 0;

    // For checking if the block is hit
    bool hit = false;

    // Block type
    BlockType type;

public:
    // Constructor
    Block(int x = 0, int y = 0, int scale = 0, UI *ui = nullptr, BlockType type = BlockType::Normal);

    // Update
    void render();

    // Check collision
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();

    // For normal blocks only
    void setHit();
    virtual bool shouldRemoveBlock();

    // Get the block ID
    BlockType getBlockID();

    // Return true if the block is hit
    bool isHit();

    //
    virtual void playerCollision(GameObject *object);
};