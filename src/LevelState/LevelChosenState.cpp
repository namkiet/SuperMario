#include <LevelState/LevelChosenState.hpp>
#include <LevelState/IntroState.hpp>

void LevelChosenState::update(GameManager *gameManager, float dt)
{
    gameManager->update(dt);
}

std::shared_ptr<LevelState> LevelChosenState::getNewState(GameManager *gameManager)
{
    if (gameManager->getStatus() == "intro")
    {
        gameManager->getWorld().setSkipUpdate(true);
        gameManager->setLives(5);
    }
    return nullptr;
}

void LevelChosenState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    gameManager->draw(window, level);
}

bool LevelChosenState::shouldReturnToMenu() const
{
    return false;
}