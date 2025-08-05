#pragma once
#include <World.hpp>
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
            sf::RectangleShape rect(box.size);
            rect.setPosition(tf.position + box.offset);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(2.f);
            rect.setFillColor(sf::Color::Transparent);
            window.draw(rect);

            // Draw lines between the corners
            for (int i = 0; i < 4; ++i)
            {
                sf::Vertex line[] = {
                    sf::Vertex(box.corners[i], sf::Color::Red),
                    sf::Vertex(box.corners[(i + 1) % 4], sf::Color::Red)};
                window.draw(line, 2, sf::Lines);
            }
        }
    }
};