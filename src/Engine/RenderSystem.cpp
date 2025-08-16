#include <iostream>
#include <Engine/Rendering/RenderSystem.hpp>
#include <iomanip>
#include <sstream>
#include <Engine/Core/DespawnTag.hpp>
#include <Core/TextureManager.hpp>

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
        sky = sf::Sprite(TextureManager::load("assets/Background/map61_1.png"));
        window.draw(sky);
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/map61_2.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    case 3:
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/map54.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    default:
        backgroundSprite = sf::Sprite(TextureManager::load("assets/Background/menu.png"));
        backgroundSprite.setScale(3, 3);
        window.draw(backgroundSprite);
        break;
    }
}