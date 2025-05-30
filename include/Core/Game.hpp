#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
                            Game();
    void                    run();

private:
    void                    handleEvent();
    void                    update(float dt);
    void                    draw();

private:
    sf::ContextSettings     contextSettings;
    sf::RenderWindow        window;
    sf::CircleShape         shape;
};