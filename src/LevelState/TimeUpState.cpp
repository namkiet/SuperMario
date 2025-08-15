#include <LevelState/TimeUpState.hpp>
#include <iostream>
#include <LevelState/IntroState.hpp>
#include <LevelManager.hpp>

void TimeUpState::update(GameManager *gameManager, float dt)
{
    if (GameManager::getLives() > 1)
    {
        return;
    }
    timeElapsed += dt;
}

std::shared_ptr<LevelState> TimeUpState::getNewState(GameManager *gameManager)
{
    if (GameManager::getLives() > 1)
    {
        LevelManager::instance().setSkipUpdate(true);
        return std::make_shared<IntroState>();
    }
    return nullptr;
}

void TimeUpState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // std::cout << "Rendering TimeUpState" << std::endl;
    // Render the time up state, e.g., show a message or animation
    sf::Text text;
    text.setFont(font);
    text.setString("Time Up!");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color({255, 49, 49, 255}));
    text.setPosition(250, 200);

    window.draw(text);
}

TimeUpState::TimeUpState()
{
    font.loadFromFile("BalooBhai2-ExtraBold.ttf");
}

bool TimeUpState::shouldReturnToMenu() const
{
    if (timeElapsed > 1.5f)
        return true;
    return false;
}