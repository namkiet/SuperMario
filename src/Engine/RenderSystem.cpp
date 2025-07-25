#include <iostream>
#include <Engine/Rendering/RenderSystem.hpp>
#include <iomanip>
#include <sstream>

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
        scoreText.setPosition(100.f, 10.f);
        scoreText.setFillColor(sf::Color::White);

        // Format score as 6 digits with leading zeros
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << scoreComponent.score;

        sf::Text scoreValueText;
        scoreValueText.setFont(font);
        scoreValueText.setString(oss.str());
        scoreValueText.setCharacterSize(25);
        scoreValueText.setPosition(100.f, 35.f);
        scoreValueText.setFillColor(sf::Color::White);

        window.draw(scoreValueText);
        window.draw(scoreText);
    }
}