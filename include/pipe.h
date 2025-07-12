#pragma once
#include "gameObject.h"
#include <vector>
#include "UI.h"

class Pipe : public GameObject
{
private:
    bool enterable;

    // For textures
    std::vector<sf::Texture> pipeTextures;

    //
    int index = 0;

public:
    Pipe() = default; // Default constructor
    Pipe(int x, int y, int width, int height, int index, int scale, bool enterable,
         UI *ui, sf::RenderWindow &window);

    // Update
    void tick();
    void render();

    // Check for collision
    sf::FloatRect getBounds();
    sf::FloatRect getBoundsTop();
    sf::FloatRect getBoundsRight();
    sf::FloatRect getBoundsLeft();

    //

    ~Pipe() = default; // Default destructor
};