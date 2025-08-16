#pragma once
#include "ICommand.hpp"
#include <SFML/Graphics.hpp>

class PanCommand : public ICommand
{
public:
    PanCommand(const sf::RenderWindow& window, sf::Vector2f& camCenter) : window(window), camCenter(camCenter) {}

    bool execute() override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);

        if (!isPanning)
        {
            // first frame of pan
            isPanning = true;
            lastMousePos = mousePixelPos;
        }
        else
        {
            // compute delta in *world* coordinates
            sf::Vector2f prevWorld = window.mapPixelToCoords(lastMousePos);
            sf::Vector2f currWorld = window.mapPixelToCoords(mousePixelPos);
            sf::Vector2f delta = prevWorld - currWorld;

            camCenter += delta;

            lastMousePos = mousePixelPos;
        }

        return false; // still running
    }

private:
    bool isPanning = false;
    sf::Vector2i lastMousePos;
    const sf::RenderWindow& window;
    sf::Vector2f& camCenter;
};
