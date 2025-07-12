#include <iostream>
#include "pipe.h"
using namespace std;

Pipe::Pipe(int x, int y, int width, int height, int index, int scale, bool enterable, UI *ui, sf::RenderWindow &window)
    : GameObject(x, y, ObjectID::Pipe, width, height, scale, window, ui), enterable(enterable), index(index)
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

sf::FloatRect Pipe::getBounds()
{
    sf::FloatRect bounds{getX() + getWidth() / 2 - getWidth() / 4,
                         getY() + getHeight() / 2 + getHeight() / 4,
                         getWidth() / 2,
                         getHeight() / 4};
    return bounds;
}

void Pipe::render()
{
    sf::Sprite sprite;
    sprite.setTexture(pipeTextures[index]);
    sprite.setPosition(getX(), getY());
    sprite.setScale(getScale(), getScale());
    getWindow().draw(sprite); // Draw the pipe sprite
}

void Pipe::tick() {}

sf::FloatRect Pipe::getBoundsTop()
{
    sf::FloatRect boundsTop{getX(),
                            getY(),
                            getWidth(),
                            getHeight() / 4};
    return boundsTop;
}

sf::FloatRect Pipe::getBoundsRight()
{
    sf::FloatRect boundsRight{getX() + getWidth() - getWidth() / 4,
                              getY(),
                              getWidth() / 4,
                              getHeight()};
    return boundsRight;
}

sf::FloatRect Pipe::getBoundsLeft()
{
    sf::FloatRect boundsLeft{getX(),
                             getY(),
                             getWidth() / 4,
                             getHeight()};
    return boundsLeft;
}
