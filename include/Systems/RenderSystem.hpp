#pragma once
#include <World.hpp>
#include <Components/Camera.hpp>
#include <Components/Sprite2D.hpp>
#include <Components/Transform.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class RenderSystem : public System
{
public:
    void update(World&, float) override
    {
        // no-op
    }

    void draw(const World& world, sf::RenderWindow& window) const
    {
        auto camOffset = world.findFirst<Camera>()->getComponent<Camera>().target;
        std::cout << camOffset.x << " " << camOffset.y << "\n";
        for (Entity* entity : world.findAll<Transform, Sprite2D>())
        {
            auto pos = entity->getComponent<Transform>().getPosition();
            auto sz = entity->getComponent<Transform>().getSize();
            auto sp = entity->getComponent<Sprite2D>().sprite;
            sp.setPosition(pos - camOffset);
            sp.setScale(sz.x / sp.getGlobalBounds().width, sz.y / sp.getGlobalBounds().height);

            if (entity->hasComponent<BoxCollider2D>())
            {
                auto& box = entity->getComponent<BoxCollider2D>();
                sf::RectangleShape rect(box.size);
                rect.setPosition(pos + box.offset- camOffset);
                rect.setOutlineColor(sf::Color::Red);
                rect.setOutlineThickness(2.f);
                rect.setFillColor(sf::Color::Transparent);
                window.draw(rect);
            }

            window.draw(sp);
        }
    }
};