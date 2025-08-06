#pragma once
#include <World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
class GameManager
{
public:
    // Default constructor
    GameManager() = delete;

    // Constructor with level
    GameManager(int level);

    void handleEvent(const sf::Event &event);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level) const;

private:
    World &world = World::getInstance();
    LevelHandler levelHandler;
    int level = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
};
