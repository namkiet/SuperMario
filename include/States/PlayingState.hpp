#pragma once
#include "GameState.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <LevelState/LevelState.hpp>
#include <LevelManager.hpp>

class PlayingState : public GameState
{
public:
    PlayingState();
    void handleEvent(Game &game, const sf::Event &event) override;
    void update(Game &game, float dt) override;
    void render(Game &game, sf::RenderWindow &window) override;
    void setLevel(int level);
    void requestLevelReload(int newLevel);
    ~PlayingState() override;
    void reset();

private:
    GameManager *gameManager;
    std::shared_ptr<LevelState> currentLevelState;
    int level = 1;
};
