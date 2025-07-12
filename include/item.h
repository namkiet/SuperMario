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

public:
    // Constructor
    Item() = default;
    Item(float x, float y, int scale, UI *ui, sf::RenderWindow &window, ItemType type);

    // Update
    void tick();
    void render();

    // Check collision
    virtual void playerCollision();
    virtual void pipeCollision(GameObject *object);
    virtual void blockCollision(GameObject *object);

    // Bounds
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

    virtual bool shouldRemoveItem();
    virtual void enemyCollision();

    bool isStomped();

    ItemType getItemType();
};