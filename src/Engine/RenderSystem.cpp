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

void RenderSystem::backgroundRender(sf::RenderWindow &window, int level) const
{
    sf::Sprite sky;
    sf::Sprite backgroundSprite;

    switch (level)
    {
    case 1:
        sky = sf::Sprite(TextureManager::load("assets/Background/map11_1.png"));
        window.draw(sky);
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/map11_2.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    case 2:
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/map54.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    case 3:
        sky = sf::Sprite(TextureManager::load("assets/Background/map61_1.png"));
        window.draw(sky);
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/map61_2.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    }
}