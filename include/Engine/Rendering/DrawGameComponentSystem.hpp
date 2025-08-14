#pragma once
#include <World.hpp>

#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Core/DespawnTag.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <Engine/Animation/Animation.hpp>

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

#include <Core/TextureManager.hpp>
#include <Gameplay/GameProperties/Components.hpp>
#include <Gameplay/Item/Components.hpp>

#include <Prefabs/Mario.hpp>

class DrawGameComponentSystem : public System
{
private:
    sf::Font font;

public:
    DrawGameComponentSystem()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }

    void update(World &, float) override
    {
        // no-op
    }

    void draw(const World &world, sf::RenderWindow &window) const
    {
        window.setView(window.getDefaultView());
        Entity *gameSession = world.findFirst<TimeComponent, LevelComponent, CoinComponent, ThemeComponent>();
        if (!gameSession)
        {
            return; // No game session found, nothing to draw
        }

        // Take the time component from the game session
        auto &timeComponent = gameSession->getComponent<TimeComponent>();

        // Render time
        sf::Text time = textRender("TIME", 700.f, 35.f, font, 25);

        // Render time value
        std::ostringstream timeOss;
        timeOss << std::setw(3) << std::setfill('0') << timeComponent.timer;
        sf::Text timeValue = textRender(timeOss.str(), 720.f, 65.f, font, 25);

        // Draw time and time value
        window.draw(time);
        window.draw(timeValue);

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

        // Take the coin component from the game session
        auto &coinComponent = gameSession->getComponent<CoinComponent>();

        // Render coin count
        std::ostringstream coinOss;
        coinOss << "x" << std::setw(2) << std::setfill('0') << coinComponent.coins;
        sf::Text coinValue = textRender(coinOss.str(), 350.f, 65.f, font, 25);

        // Draw coin count
        window.draw(coinValue);

        sf::Text worldName = textRender("WORLD", 500.f, 35.f, font, 25);
        sf::Text mapName;

        // Take the level component from the game session
        auto &levelComponent = gameSession->getComponent<LevelComponent>();

        // Render map name based on the current level
        switch (levelComponent.currentLevel)
        {
        case 1:
            mapName = textRender("1-1", 520.f, 65.f, font, 25);
            break;
        case 2:
            mapName = textRender("6-1", 520.f, 65.f, font, 25);
            break;
        case 3:
            mapName = textRender("5-4", 520.f, 65.f, font, 25);
            break;
        default:
            mapName = textRender("Unknown Level", 520.f, 65.f, font, 25);
        }

        // Draw world name and map name
        window.draw(worldName);
        window.draw(mapName);
    }
};