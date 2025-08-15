#include <LevelState/GameOverState.hpp>
#include <LevelState/IntroState.hpp>

GameOverState::GameOverState()
{
    font.loadFromFile("BalooBhai2-ExtraBold.ttf");
}

void GameOverState::update(GameManager *gameManager, float dt)
{
    timeElapsed += dt;
}

void GameOverState::render(GameManager *gameManager, sf::RenderWindow &window, int level)
{
    // Render game over screen
    window.clear(sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setString("Game Over");
    text.setCharacterSize(80);
    text.setFillColor(sf::Color({255, 49, 49, 255}));
    text.setPosition(250, 200);

    window.draw(text);
}

std::shared_ptr<LevelState> GameOverState::getNewState(GameManager *gameManager)
{
    return nullptr; // Placeholder, replace with actual logic if needed
}

bool GameOverState::shouldReturnToMenu() const
{
    if (timeElapsed > 1.5f)
        return true;
    return false;
}