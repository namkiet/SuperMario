#include <iostream>
#include "animation.h"
#include <raylib.h>
using namespace std;

Animation::Animation(int speed, std::vector<Texture2D> frameTextures)
    : speed(speed), count(0)
{
    this->frameTextures = frameTextures;
    frames = frameTextures.size();
    if (frames == 0)
    {
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
    if (currentFrame.id != 0) // Check if the texture is loaded
    {
        Rectangle sourceRect;
        Rectangle destRect;
        if (scaleX < 0)
        {
            sourceRect = {(float)currentFrame.width, 0.0f, -(float)currentFrame.width, (float)currentFrame.height};
            destRect = {(float)x, (float)y, scaleX, scaleY};
        }
        else
        {
            sourceRect = {0.0f, 0.0f, (float)currentFrame.width, (float)currentFrame.height};
            destRect = {(float)x, (float)y, scaleX, scaleY};
        }
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(currentFrame, sourceRect, destRect, origin, 0.0f, WHITE);
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
