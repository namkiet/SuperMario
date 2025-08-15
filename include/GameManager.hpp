#pragma once

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>

#include <World.hpp>

class GameManager
{
public:
    GameManager(int level, std::function<void(int)> reloadCallback);

    void handleEvent(const sf::Event &event);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level) const;

    World &getWorld();

    std::string getStatus();

    bool getShouldLoadNextLevel();
    void setShouldLoadNextLevel(bool value);
    static int getLives();
    static void setLives(int newLives);
    ~GameManager();

private:
    World world;
    LevelHandler levelHandler;
    ScoreUI *scoreUI = nullptr;
    int level = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
    bool shouldLoadNextLevel = false;
    static int lives;
};
