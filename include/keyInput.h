#pragma once
#include <SFML/Graphics.hpp>
#include "handler.h"
class KeyInput
{
private:
    bool keyDown[4];
    Handler &handler;
    sf::Event &event;

public:
    // Constructor
    KeyInput() = default;

    KeyInput(Handler &handler, sf::Event &event);

    void keyPressed();

    void keyReleased();

    void eventUpdate(sf::Event &event);

    // Destructor
    ~KeyInput() = default;
};