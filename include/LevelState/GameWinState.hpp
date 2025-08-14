#pragma once

#include <LevelState/LevelState.hpp>

class GameWinState : public LevelState
{
public:
    void update(GameManager *gameManager, float dt) override;
    std::shared_ptr<LevelState> getNewState(GameManager *gameManager) override;
    void render(GameManager *gameManager, sf::RenderWindow &window, int level) override;
};