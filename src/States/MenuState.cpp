#include <Game.hpp>
#include <States/MenuState.hpp>

MenuState::MenuState()
{
    font.loadFromFile("arial.ttf");
    playText.setFont(font);
    playText.setString("Press Enter to Play");
    playText.setPosition(250, 250);
}

void MenuState::handleEvent(Game& game, const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            game.pushState("play");
        }
    }
}

void MenuState::update(Game&, float dt) 
{
    // no-op
}

void MenuState::render(Game&, sf::RenderWindow& window) 
{
    window.draw(playText);
}