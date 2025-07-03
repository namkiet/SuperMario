#pragma once
#include <raylib.h>
#include <vector>
#include "gameObject.h"
#include "UI.h"
#include "debris.h"

enum class BlockType
{
    Normal,
    Question,
    Coin,
    Brick,
    Hidden
};

class Block : public GameObject
{
private:
    // Load UI assets
    UI *ui;

    // Block textures
    std::vector<Texture2D> blockTextures;

    // Block properties
    float positionX;
    float positionY;
    int index = 0;

    // For debris
    bool hit = false;
    Debris *debris = nullptr;

    BlockType type;

public:
    // Constructor
    Block(int x = 0, int y = 0, int width = 0, int height = 0, int index = 0, int scale = 0, UI *ui = nullptr, BlockType type = BlockType::Normal);

    // Update
    void tick();
    void render();

    // Check collision
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();

    // For debris
    void setHit();
    bool shouldRemoveBlock();

    // Destructor
    ~Block();
};