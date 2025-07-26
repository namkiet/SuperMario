#pragma once
#include <World.hpp>
#include <Engine/Camera/Camera.hpp>
#include <Engine/Animation/Animation.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Rendering/Utility.hpp>
#include <SFML/Graphics.hpp>
#include <Gameplay/Score/Components.hpp>

class RenderSystem : public System
{
private:
    sf::Font font;
    void scoreRender(const World &world, sf::RenderWindow &window, sf::Font font) const;
    void timeRender(const World &world, sf::RenderWindow &window, sf::Font font) const;

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
        timeRender(world, window, font);
        scoreRender(world, window, font);

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