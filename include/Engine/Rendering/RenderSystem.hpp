#pragma once
#include <World.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <SFML/Graphics.hpp>
#include <Gameplay/Score/Components.hpp>
#include <iomanip>
#include <sstream>
class RenderSystem : public System
{
private:
    sf::Font font;

public:
    RenderSystem()
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

        if (world.findFirst<Camera>())
        {
            auto &cam = world.findFirst<Camera>()->getComponent<Camera>();
            auto size = window.getSize();
            sf::View view(cam.target, sf::Vector2f(size.x, size.y));
            window.setView(view);
        }

        for (Entity *entity : world.findAll<Transform, Animation>())
        {
            auto &tf = entity->getComponent<Transform>();
            auto &anim = entity->getComponent<Animation>();
            auto &sp = anim.sprite;

            // Resize sprite uniformly to fit target size
            resizeSprite(sp, tf.size);

            sp.setPosition(tf.position);

            // Flip horizontally if needed
            sf::Vector2f scale = sp.getScale();
            if (anim.flipX)
            {
                sp.setOrigin(sp.getLocalBounds().width, 0);
                scale.x = -std::abs(scale.x); // flip horizontally
            }
            else
            {
                sp.setOrigin(0, 0);
                scale.x = std::abs(scale.x); // ensure it's normal if not flipped
            }
            sp.setScale(scale);

            // // Set origin to center (important for correct flipping)
            // sp.setOrigin(sp.getLocalBounds().width / 2.f, sp.getLocalBounds().height / 2.f);

            // // Position sprite centered within the tf area
            // sf::Vector2f center;
            // center.x = tf.position.x + 0.5f * tf.size.x;
            // center.y = tf.position.y + tf.size.y - 0.5f * sp.getGlobalBounds().height;

            // sp.setPosition(center);

            window.draw(sp);

            // Draw box collider if exists
            if (entity->hasComponent<BoxCollider2D>())
            {
                auto &box = entity->getComponent<BoxCollider2D>();
                sf::RectangleShape rect(box.size);
                rect.setPosition(tf.position + box.offset);
                rect.setOutlineColor(sf::Color::Red);
                rect.setOutlineThickness(2.f);
                rect.setFillColor(sf::Color::Transparent);
                window.draw(rect);
            }
        }
    }
};