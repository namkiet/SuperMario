#include <LevelState/TimeUpState.hpp>
#include <LevelState/IntroState.hpp>
#include <LevelState/GameOverState.hpp>

#include <LevelManager.hpp>

#include <UI/UIConstant.hpp>
#include <UI/HelperBuilder.hpp>

TimeUpState::TimeUpState(Game* game) : LevelState(game)
{
}

void TimeUpState::update(GameManager *gameManager, float dt)
{
    if (GameManager::getLives() > 1)
    {
        return;
    }
    gameManager->update(dt);
    timeElapsed += dt;
}

std::shared_ptr<LevelState> TimeUpState::getNewState(GameManager *gameManager)
{
    if (GameManager::getLives() > 1)
    {
        LevelManager::instance().setSkipUpdate(true);
        return std::make_shared<IntroState>(game);
    }
    else
        return std::make_shared<GameOverState>(game);

    if (shouldRestart)
    {
        shouldRestart = false;
        LevelManager::instance().setSkipUpdate(true);
        LevelManager::instance().setLevel(LevelManager::instance().getLevel());
        gameManager->setLives(5);
    }

    return nullptr;
}

void TimeUpState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
}

bool TimeUpState::shouldReturnToMenu() const
{
    return false;
}