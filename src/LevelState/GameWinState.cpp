#include <LevelState/GameWinState.hpp>

void GameWinState::update(GameManager *gameManager, float dt)
{
    gameManager->setShouldLoadNextLevel(true);
}

void GameWinState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
}

std::shared_ptr<LevelState> GameWinState::getNewState(GameManager *gameManager)
{
    return nullptr;
}