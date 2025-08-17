#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>

MenuState::MenuState()
{
    font.loadFromFile("arial.ttf");
    playText.setFont(font);
    playText.setString("Press Enter to choose level");
    playText.setPosition(250, 250);
}

void MenuState::handleEvent(Game &game, const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto playState = game.getRegistry().getState("play");
        if (playState)
        {
            std::static_pointer_cast<PlayingState>(playState)->reset();
            game.pushState("play");
        }
        else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
        {
            auto playState = game.getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(-1);
                game.pushState("play");
            }
        }
    }
}

void MenuState::update(Game &, float dt)
{
    // no-op
}

void MenuState::render(Game &, sf::RenderWindow &window)
{
    window.draw(playText);
}