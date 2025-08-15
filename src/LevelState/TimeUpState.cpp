#include <LevelState/TimeUpState.hpp>

void TimeUpState::update(GameManager *gameManager, float dt)
{
    timeElapsed += dt;
}

std::shared_ptr<LevelState> TimeUpState::getNewState(GameManager *gameManager)
{
    return nullptr;
}

void TimeUpState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
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