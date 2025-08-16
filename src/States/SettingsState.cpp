#include <Game.hpp>
#include <States/SettingsState.hpp>

SettingsState::SettingsState() 
{
    font.loadFromFile("arial.ttf");
    info.setFont(font);
    info.setString("Settings - Press Esc to return");
    info.setPosition(200, 250);
}

void SettingsState::handleEvent(Game& game,  const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        game.popState();  // return to PlayGameState
    }
}

void SettingsState::update(Game&, float dt) 
{
    // no-op
}

void SettingsState::render(Game&, sf::RenderWindow& window)
{
    window.draw(info);
}