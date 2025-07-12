#pragma once
#include "item.h"
#include "handler.h"

enum class MushroomType
{
    Normal, // Normal mushroom
    LevelUp // Level-up mushroom
};

enum class MushroomState
{
    Normal,   // Normal state
    Collected // Collected state
};

class Mushroom : public Item
{
private:
    // For textures
    std::vector<sf::Texture> textures;

    // Timer
    int timeCount = 0;

    //
    bool isCollected = false;

    // state
    MushroomState state;

    // Handler pointer
    Handler *handler;

    //
    float originalY = 0; // Original Y position for gravity effect
    bool firstTime = true;

    // Mushroom type
    MushroomType type;

public:
    Mushroom() = default; // Default constructor
    Mushroom(float x, float y, int scale, Handler *handler, UI *ui, sf::RenderWindow &window, MushroomType type);

    // Update
    void tick();
    void render();

    // Check collision
    void collision();
    void playerCollision();
    void pipeCollision(GameObject *object);
    void blockCollision(GameObject *object);

    bool shouldRemoveItem();
    bool isStomped();
};