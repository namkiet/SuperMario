#include <Game.hpp>
#include <States/SettingsState.hpp>

SettingsState::SettingsState(std::shared_ptr<Game> game): GameState(game) 
{
    font.loadFromFile("arial.ttf");
    info.setFont(font);
    info.setString("Settings - Press Esc to return");
    info.setPosition(200, 250);
}

void SettingsState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        game->popState();  // return to PlayGameState
    }
}

void SettingsState::update(float dt) 
{
    // no-op
}

void SettingsState::render(sf::RenderWindow& window)
{
    window.draw(info);
}