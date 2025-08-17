#pragma once
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
#include <LevelEditor/LevelEditor.hpp>

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>

#include <World.hpp>

class GameManager
{
public:
    GameManager(int level);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level);

private:    
    
    static int getLives();
    static void setLives(int newLives);
    ~GameManager();

private:
    World world;
    LevelHandler levelHandler;
    LevelEditor* editor;
    int currentLevel = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
    
    static int lives;
};
