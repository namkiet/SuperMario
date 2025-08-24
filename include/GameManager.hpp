#pragma once
#include <Framework/World.hpp>
#include <SFML/Graphics.hpp>
#include <LevelHandler.hpp>
#include <Editor/Editor.hpp>

#include <LevelHandler.hpp>

#include <ScoreManager.hpp>

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class GameManager
{
public:
    enum class Mode { NewGame, LoadGame, Editor };

    GameManager(int level, bool hasWonLastLevel = false, Mode mode = Mode::NewGame, const json& data = {});

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
    bool isPaused = false;
    const bool canEdit;
    std::unordered_map<std::string, std::string> musicPathMap;

    Mode mode;
    std::string imgPath = "";

    static int lives;
    static inline json prevMarioData;

    json data;
    void init();

    friend class PlayerRespawnSystem;
    friend class LevelCompletionSystem;
    friend class InGameState;
};
