#pragma once
#include <States/GameState.hpp>
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <LevelState/LevelState.hpp>
#include <LevelManager.hpp>

class PlayingState : public GameState
{
public:
    PlayingState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
    void setLevel(int level, bool hasWonLastLevel = false, GameManager::Mode mode = GameManager::Mode::NewGame, const json& data = {});
    void requestLevelReload(int newLevel);
    void setupButton();
    ~PlayingState() override;
    void reset();

private:
    GameManager *gameManager;
    std::shared_ptr<UIComponent> uiRoot;
    sf::Font UIFont;

    std::shared_ptr<UIComponent> DeadPanel; // temp
    std::shared_ptr<LevelState> currentLevelState;
    int level = 1;
};
