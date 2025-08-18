#pragma once
#include <Editor/Command/ICommand.hpp>
#include <Engine/Core/Transform.hpp>
#include <Engine/Physics/BoxCollider2D.hpp>
#include <Engine/Physics/BlockTag.hpp>
#include <ECS/Entity.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class DragCommand : public ICommand
{
public:
    DragCommand(Entity* draggedEntity, sf::RenderWindow& window)
        : draggedEntity(draggedEntity), window(window)
    {
        if (draggedEntity && draggedEntity->hasComponent<Transform>())
        {
            initialPos = draggedEntity->getComponent<Transform>().position;
        }

        handCursor.loadFromSystem(sf::Cursor::Hand);
        arrowCursor.loadFromSystem(sf::Cursor::Arrow);
        notAllowedCursor.loadFromSystem(sf::Cursor::NotAllowed);
    }

    ~DragCommand()
    {
        window.setMouseCursor(arrowCursor); // revert cursor when command ends
    }

    bool execute() override
    {
        if (!draggedEntity) return true;

        auto& pos = draggedEntity->getComponent<Transform>().position;
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        canPlace = true;

        if (draggedEntity->hasComponent<BoxCollider2D>())
        {
            for (const auto& [collider, _, __] : draggedEntity->getComponent<BoxCollider2D>().collisions)
            {
                if ((draggedEntity->hasComponent<CanHitBlockTag>() && collider->hasComponent<BlockTag>())|| 
                    (draggedEntity->hasComponent<BlockTag>() && collider->hasComponent<CanHitBlockTag>()))
                {
                    canPlace = false;
                    break;
                }
            }
        }

        // Only drag while left mouse button is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!dragging)
            {
                // First frame of dragging: store offset
                dragOffset = mousePos - pos;
                dragging = true;
            }

            pos = mousePos - dragOffset;

            window.setMouseCursor(canPlace ? handCursor : notAllowedCursor);
            return false; // keep command active while dragging
        }
        else
        {
            if (!canPlace)
            {
                pos = initialPos;
            }

            // Mouse released: stop dragging
            dragging = false;
            return true; // finish command
        }
    }

private:
    Entity* draggedEntity = nullptr;
    sf::RenderWindow& window;

    sf::Vector2f dragOffset;
    bool dragging = false;

    sf::Cursor handCursor;
    sf::Cursor arrowCursor;
    sf::Cursor notAllowedCursor;

    sf::Vector2f initialPos;
    bool canPlace = true;
};
