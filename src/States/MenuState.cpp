#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/PlayingState.hpp>

MenuState::MenuState(std::shared_ptr<Game> game): GameState(game)
{
    font.loadFromFile("arial.ttf");
    playText.setFont(font);
    playText.setString("Press Enter to choose level");
    playText.setPosition(250, 250);
}

void MenuState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        int currentLevel = 0;
        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(1);
                game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(2);
                game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
        {
            auto playState = game->getRegistry().getState("play");
            if (playState)
            {
                std::static_pointer_cast<PlayingState>(playState)->setLevel(3);
                game->pushState("play");
            }
        }
        else if (event.key.code == sf::Keyboard::X)
        {
            game->pushState("keysettings");
        }
    }
}

void MenuState::update(float dt)
{
    // no-op
}

void MenuState::render(sf::RenderWindow &window)
{
    window.draw(playText);
}