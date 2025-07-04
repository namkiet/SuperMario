#pragma once
#include "item.h"

enum class FlowerState
{
    Normal,
    Collected
};

class Flower : public Item
{
private:
    // For animation
    Animation currentAnimation;

    // For textures
    std::vector<Texture2D> textures;

    // Flower state
    FlowerState state;

    //
    bool isCollected = false;

    UI *ui;

public:
    Flower(float x = 0, float y = 0, int scale = 0, UI *ui = nullptr);

    // Update
    void tick();
    void render();

    // Check collision
    void playerCollision();

    bool shouldRemoveItem();
    bool isStomped();
};