#include <iostream>
#include <Engine/Rendering/RenderSystem.hpp>
#include <iomanip>
#include <sstream>
#include <Engine/Core/DespawnTag.hpp>

void RenderSystem::scoreRender(const World &world, sf::RenderWindow &window, sf::Font font) const
{
    window.setView(window.getDefaultView());

    for (Entity *entity : world.findAll<ScoreComponent>())
    {
        auto &scoreComponent = entity->getComponent<ScoreComponent>();
        sf::Text scoreText;

        scoreText.setFont(font);
        scoreText.setString("MARIO");
        scoreText.setCharacterSize(25);
        scoreText.setPosition(100.f, 35.f);
        scoreText.setFillColor(sf::Color::White);

        // Format score as 6 digits with leading zeros
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << scoreComponent.score;

        sf::Text scoreValueText;
        scoreValueText.setFont(font);
        scoreValueText.setString(oss.str());
        scoreValueText.setCharacterSize(25);
        scoreValueText.setPosition(100.f, 65.f);
        scoreValueText.setFillColor(sf::Color::White);

        window.draw(scoreValueText);
        window.draw(scoreText);
    }
}

void RenderSystem::timeRender(const World &world, sf::RenderWindow &window, sf::Font font) const
{
    window.setView(window.getDefaultView());

    for (Entity *entity : world.findAll<TimeComponent>())
    {
        auto &timeComponent = entity->getComponent<TimeComponent>();
        sf::Text timeText;

        timeText.setFont(font);
        timeText.setString("TIME");
        timeText.setCharacterSize(25);
        timeText.setPosition(700.f, 35.f);
        timeText.setFillColor(sf::Color::White);
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << timeComponent.timer;

        sf::Text timeValueText;
        timeValueText.setFont(font);
        timeValueText.setString(oss.str());
        timeValueText.setCharacterSize(25);
        timeValueText.setPosition(720.f, 65.0f);
        timeValueText.setFillColor(sf::Color::White);

        window.draw(timeText);
        window.draw(timeValueText);
    }
}

void RenderSystem::coinRender(const World &world, sf::RenderWindow &window, sf::Font font) const
{
    window.setView(window.getDefaultView());

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

        sf::Text coinValueText;
        coinValueText.setFont(font);
        coinValueText.setString("x" + oss.str());
        coinValueText.setCharacterSize(25);
        coinValueText.setPosition(350.f, 65.0f);
        coinValueText.setFillColor(sf::Color::White);

        window.draw(coinValueText);
    }
}

void RenderSystem::textRender(const World &world, sf::RenderWindow &window, sf::Font font) const
{
    for (Entity *entity : world.findAll<TextComponent>())
    {
        auto &textComponent = entity->getComponent<TextComponent>();
        ++textComponent.timer;
        if (textComponent.timer > 15) // Display for 60 frames
        {
            entity->addComponent<DespawnTag>();
            continue;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(textComponent.content);
        text.setCharacterSize(15);
        textComponent.y -= 5;
        text.setPosition(textComponent.x, textComponent.y);
        text.setFillColor(sf::Color::White);

        window.draw(text);
    }
}

void RenderSystem::mapNameRender(const World &world, sf::RenderWindow &window, sf::Font font) const
{
    window.setView(window.getDefaultView());

    sf::Text mapNameText;
    mapNameText.setFont(font);
    mapNameText.setString("WORLD");
    mapNameText.setCharacterSize(25);
    mapNameText.setPosition(500.f, 35.f);
    mapNameText.setFillColor(sf::Color::White);

    sf::Text mapNameValueText;
    mapNameValueText.setFont(font);
    mapNameValueText.setString("1-1");
    mapNameValueText.setCharacterSize(25);
    mapNameValueText.setPosition(520.f, 65.f);
    mapNameValueText.setFillColor(sf::Color::White);

    window.draw(mapNameText);
    window.draw(mapNameValueText);
}