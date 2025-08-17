#include <LevelState/InGameState.hpp>
#include <LevelState/GameOverState.hpp>
#include <LevelState/GameWinState.hpp>
#include <LevelState/TimeUpState.hpp>
#include <LevelState/IntroState.hpp>
#include <iostream>

InGameState::InGameState()
{
    scoreUI = new ScoreUI();
    ScoreManager::instance().addObserver(scoreUI);

    levelUI = new LevelUI();
    LevelManager::instance().addObserver(levelUI);

    coinUI = new CoinUI();
    CoinManager::instance().addObserver(coinUI);

    timeUI = new TimeUI();
    TimeManager::instance().addObserver(timeUI);
}

void InGameState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
}

std::shared_ptr<LevelState> InGameState::getNewState(GameManager *gameManager)
{
    if (LevelManager::instance().getStatus() == std::string("win"))
    {
        gameManager->setLives(gameManager->getLives() + 1);
        return std::make_shared<GameWinState>();
    }

    if (LevelManager::instance().getStatus() == std::string("timeup"))
        return std::make_shared<TimeUpState>();

    if (LevelManager::instance().getStatus() == std::string("intro"))
    {
        if (GameManager::getLives() <= 1)
        {
            // std::cout << "Game Over! Returning to main menu." << std::endl;
            gameManager->setLives(4);
            return std::make_shared<GameOverState>();
        }
        LevelManager::instance().setSkipUpdate(true);
        // std::cout << "Returning to intro state." << std::endl;
        return std::make_shared<IntroState>();
    }

    return nullptr;
}

void InGameState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering InGameState" << std::endl;
    gameManager->draw(window, level);
    scoreUI->draw(window);
    levelUI->draw(window);
    coinUI->draw(window);
    timeUI->draw(window);
}

bool InGameState::shouldReturnToMenu() const
{
    return false;
}