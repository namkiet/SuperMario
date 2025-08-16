#include <LevelState/GameWinState.hpp>
#include <iostream>
#include <LevelManager.hpp>
#include <CoinManager.hpp>
#include <ScoreManager.hpp>

void GameWinState::update(GameManager *gameManager, float dt)
{
    LevelManager::instance().setShouldLoadNextLevel(true);
}

void GameWinState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout<<"Rendering GameWinState" << std::endl;
}

std::shared_ptr<LevelState> GameWinState::getNewState(GameManager *gameManager)
{
    return nullptr;
}

bool GameWinState::shouldReturnToMenu() const
{
    return false;
}