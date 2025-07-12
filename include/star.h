#pragma once
#include "item.h"
#include "handler.h"

enum class StarState
{
    Normal,
    Collected
};

class Star : public Item
{
private:
    // For animation
    Animation *currentAnimation;

    // For textures
    std::vector<sf::Texture> textures;

    // State
    StarState state;

    // Timer
    int timeCount = 0;

    //
    bool isCollected = false;

    // Handler pointer
    Handler *handler;

    // Original Y position for gravity effect
    float originalY = 0;

    // First time flag for gravity effect
    bool firstTime = true;

public:
    Star() = default;
    Star(float x, float y, int scale, Handler *handler,
         UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    // Check collision
    void collision();
    void playerCollision();
    void pipeCollision(GameObject *object);
    void blockCollision(GameObject *object);

    //
    bool shouldRemoveItem();
    bool isStomped();

    ~Star();
};