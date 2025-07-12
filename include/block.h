#pragma once
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

    // Block textures
    std::vector<sf::Texture> blockTextures;

    int index = 0;

    // For checking if the block is hit
    bool hit = false;

    // Block type
    BlockType type;

public:
    // Constructor
    Block() = default;
    Block(int x, int y, int scale, UI *ui, sf::RenderWindow &window, BlockType type);

    // Update
    void render();

    // Check collision
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

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