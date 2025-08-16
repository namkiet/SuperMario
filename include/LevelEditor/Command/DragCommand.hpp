#pragma once
#include <LevelEditor/Command/ICommand.hpp>
#include <ECS/Entity.hpp>
#include <SFML/Graphics.hpp>

class DragCommand : public ICommand
{
public:
    DragCommand(Entity* draggedEntity, const sf::RenderWindow& window) 
        : draggedEntity(draggedEntity), window(window) {}

    bool execute() override
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return true;
        if (!draggedEntity) return true;
        if (!draggedEntity->hasComponent<Transform>()) return true;
        auto& pos = draggedEntity->getComponent<Transform>().position;

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));        

        if (!foundOffset)
        {
            dragOffset = mousePos - pos;
            foundOffset = true;
        }

        pos = mousePos - dragOffset;
        return false;        
    }

private:
    Entity* draggedEntity = nullptr;
    const sf::RenderWindow& window;

    sf::Vector2f dragOffset;
    bool foundOffset = false;
};
