#pragma once

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>

#include <World.hpp>

class GameManager
{
public:
    GameManager(int level);

    void handleEvent(const sf::Event &event);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level) const;

    
    static int getLives();
    static void setLives(int newLives);
    ~GameManager();

private:
    World world;
    LevelHandler levelHandler;
    int level = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
    
    static int lives;
};
