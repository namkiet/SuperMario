#pragma once
#include <Editor/Command/ICommand.hpp>
#include <Engine/Core/Transform.hpp>
#include <Entity/Entity.hpp>
#include <SFML/Graphics.hpp>

class ResizeCommand : public ICommand
{
public:
    ResizeCommand(Entity* entity, sf::RenderWindow& window,
                  bool resizeLeft, bool resizeTop, bool resizeRight, bool resizeBottom)
        : entity(entity), window(window),
          resizeLeft(resizeLeft), resizeTop(resizeTop),
          resizeRight(resizeRight), resizeBottom(resizeBottom)
    {
        if (entity && entity->hasComponent<Transform>())
        {
            auto& tf = entity->getComponent<Transform>();
            initialPos  = tf.position;
            initialSize = tf.size;
        }

        // load cursors
        arrowCursor.loadFromSystem(sf::Cursor::Arrow);
        if ((resizeLeft && resizeTop) || (resizeRight && resizeBottom))
            resizeCursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
        else if ((resizeRight && resizeTop) || (resizeLeft && resizeBottom))
            resizeCursor.loadFromSystem(sf::Cursor::SizeBottomLeftTopRight);
        else if (resizeLeft || resizeRight)
            resizeCursor.loadFromSystem(sf::Cursor::SizeHorizontal);
        else if (resizeTop || resizeBottom)
            resizeCursor.loadFromSystem(sf::Cursor::SizeVertical);

        window.setMouseCursor(resizeCursor);
    }

    ~ResizeCommand()
    {
        window.setMouseCursor(arrowCursor); // revert
    }

    bool execute() override
    {
        if (!entity || !entity->hasComponent<Transform>()) return true;

        auto& tf = entity->getComponent<Transform>();
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f newPos = tf.position;
            sf::Vector2f newSize = tf.size;

            // --- xử lý resize ---
            if (resizeLeft)
            {
                float diff = newPos.x - mousePos.x;
                newSize.x += diff;
                newPos.x = mousePos.x;
            }
            if (resizeRight)
            {
                newSize.x = mousePos.x - newPos.x;
            }
            if (resizeTop)
            {
                float diff = newPos.y - mousePos.y;
                newSize.y += diff;
                newPos.y = mousePos.y;
            }
            if (resizeBottom)
            {
                newSize.y = mousePos.y - newPos.y;
            }

            // clamp size để không âm
            newSize.x = std::max(newSize.x, 1.f);
            newSize.y = std::max(newSize.y, 1.f);

            // --- gán lại vào transform ---
            tf.position = newPos;
            tf.size = newSize;

            // --- đồng bộ collider ---
            if (entity->hasComponent<BoxCollider2D>())
            {
                auto& box = entity->getComponent<BoxCollider2D>();
                box.size = newSize;
                box.offset = {0.f, 0.f}; // giả sử collider nằm đúng theo transform
            }

            return false; // vẫn đang resize
        }
        else
        {
            return true; // kết thúc khi thả chuột
        }
    }


private:
    Entity* entity;
    sf::RenderWindow& window;

    sf::Vector2f initialPos;
    sf::Vector2f initialSize;

    bool resizeLeft, resizeTop, resizeRight, resizeBottom;

    sf::Cursor resizeCursor;
    sf::Cursor arrowCursor;
};
