#include "PlayingState.hpp"
#include "Game.hpp"

PlayingState::PlayingState() 
{
    // no-op
}

void PlayingState::handleEvent(Game& game, sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            game.popState();
            game.pushState("menu");
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            game.pushState("settings");
        }
    }
    
    world.handleEvent(event);
}

void PlayingState::update(Game&, float dt) 
{
    world.update(dt);
}

void PlayingState::render(Game&, sf::RenderWindow& window)
{
    world.draw(window);
}