#pragma once
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
#include <Editor/Editor.hpp>

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>

class GameManager
{
public:
    GameManager(int level, bool hasWonLastLevel);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level);
    static int getLives();
    static void setLives(int newLives);
    ~GameManager();

private:
    World world;
    LevelHandler levelHandler;
    Editor* editor = nullptr;
    int currentLevel = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
    
    static int lives;
    static inline json prevMarioData;
};
