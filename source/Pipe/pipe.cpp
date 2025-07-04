#include <iostream>
#include "pipe.h"
using namespace std;

Pipe::Pipe(int x, int y, int width, int height, int index, int scale, bool enterable, UI *ui)
    : GameObject(x, y, ObjectID::Pipe, width, height, scale), enterable(enterable), ui(ui), index(index)
{
    // Constructor implementation can be added here if needed
    if (ui == nullptr)
    {
        cerr << "UI is null in Pipe constructor!" << endl;
        return;
    }
    // Load pipe textures from UI
    pipeTextures = ui->getPipe1();
}

Rectangle Pipe::getBounds()
{
    Rectangle bounds{getX() + getWidth() / 2 - getWidth() / 4,
                     getY() + getHeight() / 2 + getHeight() / 4,
                     getWidth() / 2,
                     getHeight() / 4};
    return bounds;
}

void Pipe::render()
{
    DrawTextureEx(pipeTextures[index], {getX(), getY()}, 0.0f, (float)getScale(), WHITE); // Draw the pipe texture
}

void Pipe::tick() {}

Rectangle Pipe::getBoundsTop()
{
    Rectangle boundsTop{getX(),
                        getY(),
                        getWidth(),
                        getHeight() / 4};
    return boundsTop;
}

Rectangle Pipe::getBoundsRight()
{
    Rectangle boundsRight{getX() + getWidth() - getWidth() / 4,
                          getY(),
                          getWidth() / 4,
                          getHeight()};
    return boundsRight;
}

Rectangle Pipe::getBoundsLeft()
{
    Rectangle boundsLeft{getX(),
                         getY(),
                         getWidth() / 4,
                         getHeight()};
    return boundsLeft;
}

void Pipe::showBounds()
{
    Color color = {255, 0, 0, 255};            // Semi-transparent red color
    DrawRectangleRec(getBounds(), color);      // Draw the main bounds rectangle
    DrawRectangleRec(getBoundsTop(), color);   // Draw the top bounds rectangle
    DrawRectangleRec(getBoundsRight(), color); // Draw the right bounds rectangle
    DrawRectangleRec(getBoundsLeft(), color);  // Draw the left bounds rectangle
}
