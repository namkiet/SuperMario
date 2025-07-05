#include <iostream>
#include <raylib.h>
#include "keyInput.h"
using namespace std;

KeyInput::KeyInput(Handler &handler) : handler(handler)
{
    for (int i = 0; i < 4; ++i)
    {
        keyDown[i] = false; // Initialize all keys as not pressed
    }
}

void KeyInput::keyPressed()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        exit(0);
    }

    if (!handler.getPlayer()->isPlayerLocked())
    {
        // W for jump
        if (IsKeyDown(KEY_W))
        {
            // DrawText("W key pressed", 10, 10, 20, WHITE);
            if (handler.getPlayer() != nullptr && !handler.getPlayer()->hasJumped())
            {
                handler.getPlayer()->setVelY(-15.0f); // Jump
                handler.getPlayer()->setJump(true);
                keyDown[0] = true;
            }
        }

        // A for move left
        if (IsKeyDown(KEY_A))
        {
            if (handler.getPlayer() != nullptr)
            {
                // DrawText("A key pressed", 10, 30, 20, WHITE);
                handler.getPlayer()->setVelX(-8.0f); // Move left
                keyDown[1] = true;
            }
        }

        // D for move right
        if (IsKeyDown(KEY_D))
        {
            if (handler.getPlayer() != nullptr)
            {
                // DrawText("D key pressed", 10, 50, 20, WHITE);
                handler.getPlayer()->setVelX(8.0f); // Move right
                keyDown[2] = true;
            }
        }

        // Only for fire Mario
        if (IsKeyDown(KEY_M) && handler.getPlayer()->isFireMario())
        {
            handler.getPlayer()->fire();
            keyDown[3] = true;
        }
    }
}

void KeyInput::keyReleased()
{
    // W for jump
    if (IsKeyReleased(KEY_W))
    {
        // DrawText("W key released", 10, 70, 20, WHITE);
        keyDown[0] = false;
        // cout << handler.getPlayer()->getVelX() + handler.getPlayer()->getX() << endl;
    }

    // A for move left
    if (IsKeyReleased(KEY_A))
    {
        // DrawText("A key released", 10, 90, 20, WHITE);
        keyDown[1] = false;
    }

    // D for move right
    if (IsKeyReleased(KEY_D))
    {
        // DrawText("D key released", 10, 110, 20, WHITE);
        keyDown[2] = false;
    }

    if (IsKeyReleased(KEY_M) && handler.getPlayer()->isFireMario())
    {
        // DrawText("M key released", 10, 130, 20, WHITE);
        keyDown[3] = false;
    }

    if (!keyDown[1] && !keyDown[2])
    {
        if (handler.getPlayer() != nullptr)
        {
            handler.getPlayer()->setVelX(0.0f); // Stop horizontal movement if no keys are pressed
        }
    }
}