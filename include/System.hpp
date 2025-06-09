#pragma once
#include <SFML/Graphics.hpp>
#include <Components/Declaration.hpp>
#include <Entity.hpp>

class RenderSystem
{
public:
    void addEntity(Entity* entity)
    {
        entityList.push_back(entity);
    }

    void draw(sf::RenderWindow& window) const
    {
        for (Entity* entity : entityList)
        {
            auto pos = entity->getComponent<Transform>().getPosition();
            auto shape = entity->getComponent<Sprite2D>().getShape();
            shape.setPosition(pos);

            if (entity->hasComponent<BoxCollider2D>())
            {
                auto& box = entity->getComponent<BoxCollider2D>();
                sf::RectangleShape rect(box.size);
                rect.setPosition(pos + box.offset);
                rect.setOutlineColor(sf::Color::Red);
                rect.setOutlineThickness(2.f);
                rect.setFillColor(sf::Color::Transparent);

                window.draw(rect);
            }

            window.draw(shape);
        }
    }

private:
    std::vector<Entity*> entityList;
};