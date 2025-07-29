#include <iostream>
#include <Engine/Rendering/RenderSystem.hpp>
#include <iomanip>
#include <sstream>
#include <Engine/Core/DespawnTag.hpp>
#include <Core/TextureManager.hpp>

void RenderSystem::gameComponentRender(const World &world, sf::RenderWindow &window) const
{
    for (Entity *entity : world.findAll<TextComponent>())
    {
        auto &textComponent = entity->getComponent<TextComponent>();
        sf::Text text = textRender(textComponent.content, textComponent.x, textComponent.y, font, textComponent.size);
        window.draw(text);
    }

    window.setView(window.getDefaultView());
    for (Entity *entity : world.findAll<ScoreComponent>())
    {
        // Render player name
        sf::Text player = textRender("MARIO", 100.f, 35.f, font, 25);

        // Render score
        auto &scoreComponent = entity->getComponent<ScoreComponent>();
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << scoreComponent.score;
        sf::Text score = textRender(oss.str(), 100.f, 65.f, font, 25);

        // Draw player name and score
        window.draw(player);
        window.draw(score);
    }

    for (Entity *entity : world.findAll<TimeComponent>())
    {
        // Render time
        sf::Text time = textRender("TIME", 700.f, 35.f, font, 25);

        // Render time value
        auto &timeComponent = entity->getComponent<TimeComponent>();
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << timeComponent.timer;
        sf::Text timeValue = textRender(oss.str(), 700.f, 65.f, font, 25);

        // Draw time and time value
        window.draw(time);
        window.draw(timeValue);
    }

    for (Entity *entity : world.findAll<SmallCoinTag>())
    {
        auto &tf = entity->getComponent<Transform>();
        auto &anim = entity->getComponent<Animation>();
        auto &sp = anim.sprite;

        // Resize sprite uniformly to fit target size
        resizeSprite(sp, tf.size);

        sp.setPosition(tf.position);
        sf::Vector2f scale = sp.getScale();
        sp.setScale(scale);
        window.draw(sp);
    }

    for (Entity *entity : world.findAll<CoinComponent>())
    {
        auto &coinComponent = entity->getComponent<CoinComponent>();
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << coinComponent.coins;
        sf::Text coinValue = textRender(oss.str(), 350.f, 65.f, font, 25);

        window.draw(coinValue);
    }

    sf::Text worldName = textRender("WORLD", 500.f, 35.f, font, 25);
    sf::Text mapName = textRender("1-1", 520.f, 65.f, font, 25);
    window.draw(worldName);
    window.draw(mapName);
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