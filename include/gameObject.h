#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UI.h"

enum class ObjectID
{
    Player,
    Enemy,
    Block,
    Pipe,
    Item,
    Background
};

class GameObject
{
public:
    GameObject() = default;
    GameObject(float x, float y, ObjectID id, float width, float height, int scale, sf::RenderWindow &window, UI *ui);

    // Pure virtual method
    virtual void tick();
    virtual void render();
    virtual sf::FloatRect getBounds();      // Get the lower half bounds of the object
    virtual sf::FloatRect getBoundsTop();   // Get the upper half bounds of the object
    virtual sf::FloatRect getBoundsRight(); // Get the right half bounds of the object
    virtual sf::FloatRect getBoundsLeft();  // Get the left half bounds of the object
    virtual void showBounds();
    void applyGravity();

    // Setter methods
    void setX(float x);
    void setY(float y);
    void setID(ObjectID id);
    void setVelX(float velX);
    void setVelY(float velY);
    void setWidth(float width);
    void setHeight(float height);
    void setScale(int scale);

    void setPlayerScale(float scale);

    // Getter methods
    float getX();
    float getY();
    ObjectID getID();
    float getVelX();
    float getVelY();
    float getWidth();
    float getHeight();
    int getScale();

    // For player specific methods
    float getPlayerScale();

    // Collision checking
    virtual void collision();

    // Check if the object is dead or not
    virtual bool isDead();

    // Check if the object is stomped on or not
    virtual bool isStomped();
    virtual void setStomped(bool newState);

    // Check if the player is already check for collision
    virtual bool playerFinishedCollisionChecking();
    virtual void setPlayerFinishedCollisionChecking(bool finished);

    //
    UI *getUI();

    sf::RenderWindow &getWindow();

    // Destructor
    virtual ~GameObject();

private:
    ObjectID id;
    int screenWidth;
    int screenHeight;
    float x, y, velX, velY;
    float width, height;
    int scale;
    float playerScale; // Since they need to grow up slowly
    sf::RenderWindow &window;
    UI *ui;
};