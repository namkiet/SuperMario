#include <iostream>
#include "animation.h"
using namespace std;

Animation::Animation(int speed, std::vector<sf::Texture> frameTextures, sf::RenderWindow &window)
    : speed(speed), count(0), window(window)
{
    this->frameTextures = frameTextures;
    frames = frameTextures.size();
    if (frames == 0)
    {
        // cout<< "Error: No frames provided for animation." << endl;
        return;
    }
    else
    {
        currentFrame = this->frameTextures[0]; // Initialize with the first frame
    }
}

void Animation::runAnimation()
{
    ++index;
    if (index > speed)
    {
        index = 0;
        nextFrame();
    }
}

void Animation::nextFrame()
{
    currentFrame = frameTextures[count];
    ++count;
    if (count >= frames)
    {
        count = 0;
    }
}

void Animation::drawAnimation(int x, int y, float scaleX, float scaleY)
{
    if (currentFrame.getSize().x != 0 && currentFrame.getSize().y != 0) // Check if the texture is loaded
    {
        sf::Sprite sprite;
        sprite.setTexture(currentFrame);
        sprite.setPosition(x, y); // Set the position of the sprite
        if (scaleX < 0)
        {
            sprite.setOrigin(currentFrame.getSize().x, 0);
            sprite.setScale(scaleX / currentFrame.getSize().x, scaleY / currentFrame.getSize().y); // Set the scale of the sprite
        }
        else
        {
            sprite.setScale(scaleX / currentFrame.getSize().x, scaleY / currentFrame.getSize().y); // Set the scale of the sprite
        }
        window.draw(sprite);
    }
    else
    {
        std::cerr << "Error: Current frame texture is not loaded." << std::endl;
    }
}

void Animation::reset()
{
    index = 0;
    count = 0;
    currentFrame = frameTextures[0]; // Start at the beginning
}

int Animation::getCurrentFrameIndex()
{
    return count + 1;
}