#include <Game.hpp>
#include <States/MenuState.hpp>
#include <States/KeySettingState.hpp>
#include <UI/KeyBinding.hpp>
#include <assert.h>
#include <Engine/Rendering/Utility.hpp>
KeySettingState::KeySettingState(std::shared_ptr<Game> game): GameState(game)
{
    if (!backgroundTexture.loadFromFile("assets/Background/MenuBackground.png"))
        {
            assert(!"Can not load menuBackground");
        }

        // Set the texture to the sprite
        background.setTexture(backgroundTexture);

        // set background
        background.setPosition(0.f, 0.f);
        sf::Vector2u windowSize = game->getWindow().getSize();
        sf::Vector2f windowSizeF(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
        resizeSprite(background, windowSizeF);
}

void KeySettingState::handleEvent(const sf::Event &event)
{

}
void KeySettingState::update(float dt)
{

}
void KeySettingState::render(sf::RenderWindow &window)
{
    window.draw(background);

}