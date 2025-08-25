#pragma once
#include <Framework/World.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <SFML/Graphics.hpp>

class DrawBoxColliderSystem : public System
{
public:
    void update(World &, float) override
    {
        // no-op
    }

    void draw(const World &world, sf::RenderWindow &window) const
    {
        // return;
        for (Entity* entity : world.findAll<Transform, BoxCollider2D>())
        {
            auto &tf = entity->getComponent<Transform>();
            auto &box = entity->getComponent<BoxCollider2D>();
            sf::RectangleShape rect;
            rect.setSize(box.size);
            rect.setPosition(tf.position + box.offset);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(2.f);
            rect.setFillColor(sf::Color::Transparent);
            window.draw(rect);
        }
    }
};