#include <iostream>
#include <Engine/Rendering/RenderSystem.hpp>
#include <iomanip>
#include <sstream>
#include <Engine/Core/DespawnTag.hpp>
#include <Core/TextureManager.hpp>

void RenderSystem::textComponentRender(const World &world, sf::RenderWindow &window) const
{
    for (Entity *entity : world.findAll<TextComponent>())
    {
        auto &textComponent = entity->getComponent<TextComponent>();
        sf::Text text = textRender(textComponent.content, textComponent.startX, textComponent.startY, font, textComponent.size);
        window.draw(text);
    }
}

void RenderSystem::backgroundRender(sf::RenderWindow &window) const
{
    // window.setView(view);
    sf::Sprite sky(TextureManager::load("assets/Background/map11_1.png"));
    window.draw(sky);
    sf::Sprite backgroundSprite(TextureManager::load("assets/Background/map11.png"));
    // float scaleX = SIZE::SCREEN.x / backgroundSprite.getGlobalBounds().width;
    backgroundSprite.setScale(3, 3);
    window.draw(backgroundSprite);
}