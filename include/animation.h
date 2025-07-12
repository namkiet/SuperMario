#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Animation
{
private:
    int speed, frames, index = 0;
    int count = 0;
    sf::Texture currentFrame;
    std::vector<sf::Texture> frameTextures;
    void nextFrame();
    sf::RenderWindow &window; // Reference to the window to draw the animation

public:
    // Constructor
    Animation() = default; // Default constructor
    Animation(int speed, std::vector<sf::Texture> frameTextures, sf::RenderWindow &window);

    // Run and draw animation
    void runAnimation();
    void drawAnimation(int x, int y, float scaleX, float scaleY);

    // Reset the animation
    void reset();

    // For player
    int getCurrentFrameIndex();

};
