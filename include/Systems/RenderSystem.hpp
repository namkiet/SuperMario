#pragma once
#include <World.hpp>
#include <Components/Camera.hpp>
#include <Components/Animation.hpp>
#include <Components/Transform.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

inline void resizeSprite(sf::Sprite& sprite, const sf::Vector2f& targetSize)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    float scaleX = targetSize.x / bounds.width;
    float scaleY = targetSize.y / bounds.height;
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);
}


class RenderSystem : public System
{
public:
    void update(World&, float) override
    {
        // no-op
    }

    void draw(const World& world, sf::RenderWindow& window) const
    {
        auto& cam = world.findFirst<Camera>()->getComponent<Camera>();
        auto size = window.getSize();
        sf::View view(cam.target, sf::Vector2f(size.x, size.y));
        window.setView(view);

        for (Entity* entity : world.findAll<Transform, Animation>())
        {
            auto& tf = entity->getComponent<Transform>();
            auto& anim = entity->getComponent<Animation>();
            auto& sp = anim.sprite;

            // Resize sprite uniformly to fit target size
            resizeSprite(sp, tf.size);

            // Flip horizontally if needed
            sf::Vector2f scale = sp.getScale();
            if (anim.flipX) 
            {
                scale.x = -std::abs(scale.x);  // flip horizontally
            } 
            else 
            {
                scale.x = std::abs(scale.x);   // ensure it's normal if not flipped
            }
            sp.setScale(scale);

            // Set origin to center (important for correct flipping)
            sp.setOrigin(sp.getLocalBounds().width / 2.f, sp.getLocalBounds().height / 2.f);

            // Position sprite centered within the tf area
            sf::Vector2f center = tf.position + 0.5f * tf.size;
            sp.setPosition(center);

            // resizeSprite(sp, tf.size);
            // sp.setPosition(tf.position);
            window.draw(sp);

            // Draw box collider if exists
            if (entity->hasComponent<BoxCollider2D>()) 
            {
                auto& box = entity->getComponent<BoxCollider2D>();
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