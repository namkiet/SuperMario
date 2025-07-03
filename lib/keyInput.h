#pragma once
#include <raylib.h>
#include "handler.h"
class KeyInput
{
private:
    bool keyDown[4];
    Handler &handler;

public:
    KeyInput(Handler &handler);
    void keyPressed();
    void keyReleased();
    ~KeyInput() = default; // Default destructor
};