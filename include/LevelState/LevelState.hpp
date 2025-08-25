#pragma once
#include <GameManager.hpp>

#include <UI/Composite.hpp>
#include <memory>
#include <Game.hpp>
class LevelState
{
protected:
    Game* game;
    std::shared_ptr<UIComponent> uiRoot;
    sf::Font UIFont;
    friend class PlayingState;
public:
    LevelState() {
        uiRoot = nullptr;
    }
    LevelState(Game* game): game(game) {
        uiRoot = nullptr;
        UIFont.loadFromFile("BalooBhai2-ExtraBold.ttf");
    }
    virtual void update(GameManager *gameManager, float dt) = 0;
    virtual std::shared_ptr<LevelState> getNewState(GameManager *gameManager) = 0;
    virtual void render(GameManager *gameManager, sf::RenderWindow &window, int level) = 0;
    virtual bool shouldReturnToMenu() const = 0;
};