#include <LevelState/LevelChosenState.hpp>
#include <LevelState/IntroState.hpp>
#include <LevelManager.hpp>
#include <CoinManager.hpp>
#include <ScoreManager.hpp>
void LevelChosenState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
}

std::shared_ptr<LevelState> LevelChosenState::getNewState(GameManager *gameManager)
{
    if (LevelManager::instance().getStatus() == std::string("intro"))
    {
        LevelManager::instance().setSkipUpdate(true);
        gameManager->setLives(5);
        CoinManager::instance().reset();
        ScoreManager::instance().reset();
        LevelManager::instance().reset();
    }
    return nullptr;
}

void LevelChosenState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering LevelChosenState" << std::endl;
    gameManager->draw(window, level);
}

bool LevelChosenState::shouldReturnToMenu() const
{
    return false;
}