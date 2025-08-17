#pragma once
#include <GameManager.hpp>

class LevelState
{
public:
    virtual void update(GameManager *gameManager, float dt) = 0;
    virtual std::shared_ptr<LevelState> getNewState(GameManager *gameManager) = 0;
    virtual void render(GameManager *gameManager, sf::RenderWindow &window, int level) = 0;
    virtual bool shouldReturnToMenu() const = 0;
};