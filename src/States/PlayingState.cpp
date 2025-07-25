#include <Game.hpp>
#include <States/PlayingState.hpp>
#include <Core/Variables.hpp>
PlayingState::PlayingState() 
{
    // no-op
}

void PlayingState::handleEvent(Game& game, const sf::Event& event)
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
    
    gameManager.handleEvent(event);
}

void PlayingState::update(Game&, float dt) 
{
    gameManager.update(dt);
}

void PlayingState::render(Game&, sf::RenderWindow& window)
{
    // window.setView(view);
    sf::Sprite backgroundSprite(TextureManager::load("assets/Background/map11_1.png"));
    // float scaleX = SIZE::SCREEN.x / backgroundSprite.getGlobalBounds().width;
    float scaleY = SIZE::SCREEN.y / backgroundSprite.getGlobalBounds().height;
    backgroundSprite.setScale(1, scaleY);
    window.draw(backgroundSprite);

    gameManager.draw(window);
}