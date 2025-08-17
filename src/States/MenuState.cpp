#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>

MenuState::MenuState()
{
    font.loadFromFile("arial.ttf");
    playText.setFont(font);
    playText.setString("Press 1 to start World 1-1 \nPress 2 to start World 6-1 \nPress 3 to start World 5-4\nPress 4 to continue saved game");
    playText.setPosition(250, 250);
}

void MenuState::handleEvent(Game &game, const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        int currentLevel = 0;
        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
        {
            auto playState = game.getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(1);
                game.pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
        {
            auto playState = game.getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(2);
                game.pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
        {
            auto playState = game.getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(3);
                game.pushState("play");
            }
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