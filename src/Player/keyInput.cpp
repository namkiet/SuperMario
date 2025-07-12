#include <iostream>
#include "keyInput.h"
using namespace std;

KeyInput::KeyInput(Handler &handler, sf::Event &event) : handler(handler), event(event)
{
    // cout << "In KeyInput constructor" << endl;
    for (int i = 0; i < 4; ++i)
    {
        keyDown[i] = false; // Initialize all keys as not pressed
    }
}

void KeyInput::keyPressed()
{
    if (!handler.getPlayer()->isPlayerLocked())
    {
        // W for jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            // cout << "W key pressed" << endl;
            if (handler.getPlayer() != nullptr && !handler.getPlayer()->hasJumped())
            {
                handler.getPlayer()->setVelY(-15.0f); // Jump
                handler.getPlayer()->setJump(true);
                keyDown[0] = true;
            }
        }

        // A for move left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (handler.getPlayer() != nullptr)
            {
                // cout << "A key pressed" << endl;
                handler.getPlayer()->setVelX(-8.0f); // Move left
                keyDown[1] = true;
            }
        }

        // D for move right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (handler.getPlayer() != nullptr)
            {
                // cout << "D key pressed" << endl;
                handler.getPlayer()->setVelX(8.0f); // Move right
                keyDown[2] = true;
            }
        }

        // Only for fire Mario
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && handler.getPlayer()->isFireMario())
        {
            handler.getPlayer()->fire();
            keyDown[3] = true;
        }
    }
}

void KeyInput::keyReleased()
{
    // W for jump
    if (event.key.code == sf::Keyboard::W && event.type == sf::Event::KeyReleased)
    {
        // DrawText("W key released", 10, 70, 20, WHITE);
        keyDown[0] = false;
        // cout << handler.getPlayer()->getVelX() + handler.getPlayer()->getX() << endl;
    }

    // A for move left
    if (event.key.code == sf::Keyboard::A && event.type == sf::Event::KeyReleased)
    {
        // DrawText("A key released", 10, 90, 20, WHITE);
        keyDown[1] = false;
    }

    // D for move right
    if (event.key.code == sf::Keyboard::D && event.type == sf::Event::KeyReleased)
    {
        // DrawText("D key released", 10, 110, 20, WHITE);
        keyDown[2] = false;
    }

    if (event.key.code == sf::Keyboard::M && event.type == sf::Event::KeyReleased && handler.getPlayer()->isFireMario())
    {
        // DrawText("M key released", 10, 130, 20, WHITE);
        keyDown[3] = false;
    }

    if (!keyDown[1] && !keyDown[2] && !handler.getPlayer()->isPlayerLocked())
    {
        if (handler.getPlayer() != nullptr)
        {
            handler.getPlayer()->setVelX(0.0f); // Stop horizontal movement if no keys are pressed
        }
    }
}

void KeyInput::eventUpdate(sf::Event &event)
{
    this->event = event;
}