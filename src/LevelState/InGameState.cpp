#include <LevelState/InGameState.hpp>
#include <LevelState/GameOverState.hpp>
#include <LevelState/GameWinState.hpp>
#include <LevelState/TimeUpState.hpp>
#include <LevelState/IntroState.hpp>
#include <iostream>

void InGameState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
}

std::shared_ptr<LevelState> InGameState::getNewState(GameManager *gameManager)
{
    if (gameManager->getStatus() == std::string("win"))
        return std::make_shared<GameWinState>();

    if (gameManager->getStatus() == std::string("timeup"))
        return std::make_shared<TimeUpState>();

    if (gameManager->getStatus() == std::string("intro"))
    {
        if (GameManager::getLives() <= 1)
        {
            gameManager->setLives(4);
            return std::make_shared<GameOverState>();
        }
        gameManager->getWorld().setSkipUpdate(true);
        return std::make_shared<IntroState>();
    }

    return nullptr;
}

void InGameState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    gameManager->draw(window, level);
}

bool InGameState::shouldReturnToMenu() const
{
    return false;
}