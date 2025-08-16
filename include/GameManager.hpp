#pragma once
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
#include <LevelEditor/LevelEditor.hpp>

class GameManager
{
public:
    GameManager() = delete;

    // Constructor with level
    GameManager(int level);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level);

private:    
    World world;
    LevelHandler levelHandler;
    LevelEditor editor;
    int currentLevel = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
};
