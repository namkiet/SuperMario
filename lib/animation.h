#pragma once
#include <raylib.h>
#include <vector>
class Animation
{
private:
    int speed, frames, index = 0;
    int count = 0;
    Texture2D currentFrame;
    std::vector<Texture2D> frameTextures;
    void nextFrame();

public:
    // Constructor
    Animation(int speed = 0, std::vector<Texture2D> frameTextures = {});

    // Run and draw animation
    void runAnimation();
    void drawAnimation(int x, int y, float scaleX, float scaleY);

    // Reset the animation
    void reset();

    // For player
    int getCurrentFrameIndex();
};
