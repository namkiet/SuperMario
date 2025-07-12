#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.h"

class Debris
{
private:
    // Debris texture
    std::vector<sf::Texture> debris;
    sf::Image debris_sheet;

    // Scale and dimensions
    int scale;
    int width, height;
    float velX, velY;

    // X and y coordinates
    std::vector<float> x;
    std::vector<float> y;

    // UI pointer
    UI *ui;

    //
    sf::RenderWindow &window;

public:
    // Constructor
    Debris() = default; // Default constructor
    Debris(float x, float y, float width, float height, float scale, UI *ui,
           sf::RenderWindow &window);

    // Apply gravity to debris
    void applyGravity();

    // Update
    void tick();
    void draw();

    // Should remove debris
    bool shouldRemove();
};