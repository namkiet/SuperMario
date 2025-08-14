#include <LevelState/GameOverState.hpp>
#include <LevelState/IntroState.hpp>

void GameOverState::update(GameManager *gameManager, float dt)
{
    timeElapsed += dt;
    if (timeElapsed > 1.5f)
        gameManager->setGoBackToMenu(true);
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