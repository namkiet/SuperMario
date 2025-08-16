#pragma once
#include <World.hpp>
#include <Gameplay/GameProperties/Components.hpp>

class DrawTextSystem : public System
{
private:
    sf::Font font;

public:
    DrawTextSystem()
    {
        font.loadFromFile("SuperMarioBros.ttf");
    }
    void update(World &world, float dt) override
    {
    }
    void draw(const World &world, sf::RenderWindow &window) const
    {
        for (Entity *entity : world.findAll<TextComponent>())
        {
            auto &textComponent = entity->getComponent<TextComponent>();
            sf::Text text = textRender(textComponent.content, textComponent.startX, textComponent.startY, font, textComponent.size);
            window.draw(text);
        }
    }
};