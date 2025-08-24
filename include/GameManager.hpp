#pragma once
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
#include <Editor/Editor.hpp>

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>
#include <unordered_map>

class GameManager
{
public:
    GameManager(int level, bool hasWonLastLevel, bool shouldContinue, bool allowEditing);
    void init(bool shouldContinue, bool canEdit);

    void handleEvent(const sf::Event &event, sf::RenderWindow &window);
    void update(float dt);
    void draw(sf::RenderWindow &window, int level);
    static int getLives();
    static void setLives(int newLives);
    static json &getPrevMarioData();
    ~GameManager();

private:
    World world;
    LevelHandler levelHandler;
    Editor *editor = nullptr;
    int currentLevel = 1;
    bool oneFrame = false;
    bool shouldPlay = true;
    bool isPaused = false;
    const bool canEdit;
    std::unordered_map<std::string, std::string> musicPathMap;

    static int lives;
    static inline json prevMarioData;
};
