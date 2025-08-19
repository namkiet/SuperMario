#pragma once
#include "GameState.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <LevelState/LevelState.hpp>
#include <LevelManager.hpp>

class PlayingState : public GameState
{
public:
    PlayingState(std::shared_ptr<Game> game);
    void handleEvent(const sf::Event &event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow &window) override;
    void setLevel(int level, bool hasWonLastLevel = false);
    void requestLevelReload(int newLevel);
    void setupButton();
    ~PlayingState() override;
    void reset();

private:
    GameManager *gameManager;
    std::shared_ptr<LevelState> currentLevelState;
    std::shared_ptr<UIComponent> uiRoot;
    sf::Font UIFont;

    std::shared_ptr<UIComponent> DeadPanel; // temp
    int level = 1;
};
