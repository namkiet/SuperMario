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
    Animation *currentAnimation;

    // For textures
    std::vector<sf::Texture> textures;

    // Flower state
    FlowerState state;

    //
    bool isCollected = false;

public:
    Flower() = default;
    Flower(float x, float y, int scale, UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    // Check collision
    void playerCollision();

    bool shouldRemoveItem();
    bool isStomped();

    ~Flower();
};