#pragma once
#include "gameObject.h"
#include "UI.h"
#include "animation.h"
#include <vector>

enum class ItemType
{
    Coin,
    Mushroom, // Bigger
    Flower,   // Fire
    Star,
    Fire
};

class Item : public GameObject
{
private:
    // Constant values
    static const float WIDTH;
    static const float HEIGHT;

    // Item type
    ItemType type;

    // UI pointer
    UI *ui;

public:
    // Constructor
    Item(float x = 0, float y = 0, int scale = 0, UI *ui = nullptr, ItemType type = ItemType::Coin);

    // Update
    void tick();
    void render();

    // Check collision
    virtual void playerCollision();
    virtual void pipeCollision(GameObject *object);
    virtual void blockCollision(GameObject *object);

    // Bounds
    Rectangle getBounds();
    Rectangle getBoundsTop();
    Rectangle getBoundsRight();
    Rectangle getBoundsLeft();

    virtual bool shouldRemoveItem();
    virtual void enemyCollision();

    bool isStomped();

    ItemType getItemType();
};